namespace LBNet
{
	template<typename TGameObject>
	CGameServer<TGameObject>::CGameServer() : _mConfig(nullptr)
	{
		static_assert(std::is_base_of<CGameObject, TGameObject>::value == true);
	}

	template<typename TGameObject>
	CGameServer<TGameObject>::~CGameServer()
	{
	}

	template<typename TGameObject>
	unsigned int CGameServer<TGameObject>::GetAcceptorCount()
	{
		return static_cast<unsigned int>(__mAcceptorList.size());
	}

	template<typename TGameObject>
	void CGameServer<TGameObject>::SetConfig(CConfig* pConfig)
	{
		_mConfig = pConfig;
	}

	template<typename TGameObject>
	ErrCode CGameServer<TGameObject>::Initialize()
	{
		LB_ASSERT(_mConfig != nullptr, "Must Initialize Config");

		if (_mConfig == nullptr)
			return eErrCodeInvalidConfig;

		Size aAddrCnt = _mConfig->GetAddressCnt();
		for (Size aIndex = 0; aIndex < aAddrCnt; ++aIndex)
		{
			auto aAddrInfo = _mConfig->GetAddress(static_cast<int>(aIndex));
			
			if (aAddrInfo.mIp == "")
				AddAcceptor(aAddrInfo.mPort);
			else
				AddAcceptor(aAddrInfo.mIp.c_str(), aAddrInfo.mPort);
		}

		CFactory::Instance().AddObjectPool<TGameObject>(_mConfig->GetSessionCnt());
		CFactory::Instance().AddObjectPool<CSession>(_mConfig->GetSessionCnt());
		CFactory::Instance().AddObjectPool<CTimerTask>(_mConfig->GetTimerTaskCnt());
		CFactory::Instance().AddObjectPool<CLogBuffer>(_mConfig->GetLogBufCnt());
		
		return 0;
	}

	template<typename TGameObject>
	ErrCode CGameServer<TGameObject>::LazyInitialize()
	{
		if (_mConfig == nullptr)
			return eErrCodeInvalidConfig;

		CFactory::Instance().Initialize();

		return 0;
	}

	template<typename TGameObject>
	ErrCode CGameServer<TGameObject>::Close()
	{
		for (auto& aAcceptor : __mAcceptorList)
		{
			aAcceptor->Close();
		}

		CFactory::Instance().Close();
		CIOContext::Instance().Stop();
		return 0;
	}

	template<typename TGameObject>
	ErrCode CGameServer<TGameObject>::Run()
	{
		if (_mConfig == nullptr)
			return eErrCodeInvalidConfig;

		if (__mAcceptorList.size() == 0)
		{
			return 0;
		}

		for (auto& aAcceptor : __mAcceptorList)
		{
			aAcceptor->Listen();
			__SetAccept(aAcceptor.get());
		}

		CUdpSession::Instance().ReceiveFrom();

		if (_mConfig->GetThreadCnt() < 1)
			return eErrCodeInvalidThreadCnt;

		for (unsigned int index = 0; index < _mConfig->GetThreadCnt(); ++index)
		{
			__mThreadList.emplace_back(std::thread{ std::bind(&CGameServer<TGameObject>::__Main, this) });
		}

		for (auto& aThread : __mThreadList)
		{
			aThread.join();
		}

		return 0;
	}

	template<typename TGameObject>
	void CGameServer<TGameObject>::__AddAcceptor(const char* pIp, unsigned short pPort)
	{
		UniqueObject<CAcceptor> aAcceptor = std::make_unique<CAcceptor>();
		aAcceptor->Bind(pIp, pPort);
		__mAcceptorList.emplace_back(std::move(aAcceptor));
	}

	template<typename TGameObject>
	void CGameServer<TGameObject>::__AddAcceptor(unsigned short pPort)
	{
		UniqueObject<CAcceptor> aAcceptor = std::make_unique<CAcceptor>();
		aAcceptor->Bind(pPort);
		__mAcceptorList.emplace_back(std::move(aAcceptor));
	}

	template<typename TGameObject>
	void CGameServer<TGameObject>::__Main()
	{
		try
		{
			CIOContext::Instance().Run();
		}
		catch (std::exception& aException)
		{
			LB_ASSERT(0, "Except");
			UNREFERENCED_PARAMETER(aException);
		}
	}

	template<typename TGameObject>
	ErrCode CGameServer<TGameObject>::__SetAccept(CAcceptor* pAcceptor)
	{
		auto aSession = CFactory::Instance().New<CSession>(&CSession::Delete);
		if (aSession == nullptr)
		{
			//세션 리소스 부족
			CTimer::Start(eTimeRetryAccept, [this, pAcceptor](ErrCode /*pErr*/)
			{
				__SetAccept(pAcceptor);
				return false;
			});
			return eErrCodeNotEnoughRsc;
		}

		// 게임 오브젝트는 accept후에는 부족할 수 있기 때문에 
		// accept전에 미리 연결시킨다. 연결 실패시 게임 오브젝트를 해제한다.
		auto aGameObject = CFactory::Instance().New<TGameObject>();
		if (aGameObject == nullptr)
		{
			aSession->SetDisconnect(eErrCodeNotEnoughRsc);
			CTimer::Start(eTimeRetryAccept, [this, pAcceptor](ErrCode /*pErr*/)
			{
				__SetAccept(pAcceptor);
				return false;
			});

			return eErrCodeNotEnoughRsc;
		}
		aSession->SetGameObject(aGameObject);
		aGameObject->LinkSession(aSession);
		auto aSessionPtr = aSession.get();

		pAcceptor->AcceptAsync(*aSessionPtr,
			[this, aSharedSession = std::move(aSession), pAcceptor](const boost::system::error_code& pErr) mutable
		{
			if (pErr.value() != 0)
			{
				CConsoleLog(ELogType::eLogInfo) << "Accept Fail : " << pErr.value();
				aSharedSession->SetDisconnect(pErr.value());
				__SetAccept(pAcceptor);
				return;
			}

			aSharedSession->SetShared(aSharedSession);
			ErrCode aErr = aSharedSession->OnAccept();
			if (aErr != 0)
			{
				CConsoleLog(ELogType::eLogInfo) << "Accept Fail : " << pErr.value();
				aSharedSession->SetDisconnect(aErr);
				__SetAccept(pAcceptor);

				return;
			}

			__SetAccept(pAcceptor);
		});

		return 0;
	}
}