namespace LBNet
{
	template<typename TGameObject>
	CGameServer<TGameObject>::CGameServer() : __mThreadCnt(0), __mMaxSession(100), 
		__mThreadList(), __mAcceptorList()
	{
		static_assert(std::is_base_of<CGameObject, TGameObject>::value == true);
	}

	template<typename TGameObject>
	CGameServer<TGameObject>::~CGameServer()
	{
	}

	template<typename TGameObject>
	void CGameServer<TGameObject>::AddAcceptor(const char* pIp, unsigned short pPort)
	{
		CAcceptor aAcceptor;
		aAcceptor.Bind(pIp, pPort);
		__mAcceptorList.emplace_back(std::move(aAcceptor));
	}

	template<typename TGameObject>
	void CGameServer<TGameObject>::AddAcceptor(unsigned short pPort)
	{
		CAcceptor aAcceptor;
		aAcceptor.Bind(pPort);
		__mAcceptorList.emplace_back(std::move(aAcceptor));
	}

	template<typename TGameObject>
	void CGameServer<TGameObject>::SetThreadCount(unsigned int pThread)
	{
		__mThreadCnt = (pThread == 0)? 
			std::thread::hardware_concurrency() * 2 : 
			pThread;
	}

	template<typename TGameObject>
	void CGameServer<TGameObject>::SetSessionMax(unsigned int pSession)
	{
		__mMaxSession = pSession;
	}

	template<typename TGameObject>
	unsigned int CGameServer<TGameObject>::GetThreadCount()
	{
		return __mThreadCnt;
	}

	template<typename TGameObject>
	unsigned int CGameServer<TGameObject>::GetAcceptorCount()
	{
		return static_cast<unsigned int>(__mAcceptorList.size());
	}

	template<typename TGameObject>
	unsigned int CGameServer<TGameObject>::GetSessionMax()
	{
		return __mMaxSession;
	}

	template<typename TGameObject>
	ErrCode CGameServer<TGameObject>::Initialize()
	{
		CFactory::Instance().AddObjectPool<TGameObject>(__mMaxSession);
		CFactory::Instance().AddObjectPool<CSession>(__mMaxSession);
		
		return 0;
	}

	template<typename TGameObject>
	ErrCode CGameServer<TGameObject>::LazyInitialize()
	{
		CFactory::Instance().Initialize();
		CSessionManager::Instance().Initialize(__mMaxSession);

		return 0;
	}

	template<typename TGameObject>
	ErrCode CGameServer<TGameObject>::Close()
	{
		for (auto& aAcceptor : __mAcceptorList)
		{
			aAcceptor.Close();
		}

		CSessionManager::Instance().Close();
		// CFactory는 마지막에 삭제해야 한다.
		CFactory::Instance().Close();
		return 0;
	}

	template<typename TGameObject>
	ErrCode CGameServer<TGameObject>::Run()
	{
		if (__mAcceptorList.size() == 0)
		{
			return 0;
		}

		for (auto& aAcceptor : __mAcceptorList)
		{
			__SetAccept(aAcceptor);
		}

		if (__mThreadCnt < 1)
			return 2;

		for (unsigned int index = 0; index < __mThreadCnt; ++index)
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
	void CGameServer<TGameObject>::__Main()
	{
		try
		{
			CIOContext::Instance().Run();
		}
		catch (std::exception& aException)
		{
			UNREFERENCED_PARAMETER(aException);
			// @todo 추후 예외시 덤프기능 구현하기
		}
	}

	template<typename TGameObject>
	ErrCode CGameServer<TGameObject>::__SetAccept(CAcceptor& pAcceptor)
	{
		auto aKey = CSessionManager::Instance().GetKey();
		if (aKey.mKey == 0)
		{
			//세션 리소스 부족
			return 1;
		}

		auto aSession = CSessionManager::Instance().GetSession(aKey);
		if (aSession == nullptr)
		{
			//세션 리소스 부족
			return 1;
		}

		// 게임 오브젝트는 accept후에는 부족할 수 있기 때문에 
		// accept전에 미리 연결시킨다. 연결 실패시 게임 오브젝트를 해제한다.
		aSession->OnConstruct();
		aSession->OnAccess();

		auto aGameObject = CFactory::Instance().New<TGameObject>();
		if (aGameObject == nullptr)
		{
			aSession->SetDisconnect();
			aSession->OnAccessEnd();

			LB_ASSERT(aSession->GetState() == CManagedObject::EState::eReturned, "여기에서 반납이 되어야 한다.");
			return 1;
		}

		pAcceptor.Listen();
		pAcceptor.AcceptAsync(*aSession,
			[this, &aSession](const boost::system::error_code& pErr)
		{
			if (pErr.value() != 0)
			{
				aSession->SetDisconnect();
				aSession->OnAccessEnd();
			}

			ErrCode aErr = aSession->OnAccept();
			if (aErr != 0)
			{
				aSession->SetDisconnect();
				aSession->OnAccessEnd();
				LB_ASSERT(aSession->GetState() == CManagedObject::EState::eReturned, "여기에서 반납이 되어야 한다.");
			}
		});

		return 0;
	}
}