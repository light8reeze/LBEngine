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
		// CFactory�� �������� �����ؾ� �Ѵ�.
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
			// @todo ���� ���ܽ� ������� �����ϱ�
		}
	}

	template<typename TGameObject>
	ErrCode CGameServer<TGameObject>::__SetAccept(CAcceptor& pAcceptor)
	{
		auto aKey = CSessionManager::Instance().GetKey();
		if (aKey.mKey == eKeyNull)
		{
			//���� ���ҽ� ����
			return 1;
		}

		auto aSession = CSessionManager::Instance().GetSession(aKey);
		if (aSession == nullptr)
		{
			//���� ���ҽ� ����
			return 1;
		}

		// ���� ������Ʈ�� accept�Ŀ��� ������ �� �ֱ� ������ 
		// accept���� �̸� �����Ų��. ���� ���н� ���� ������Ʈ�� �����Ѵ�.
		aSession->OnConstruct();
		aSession->OnAccess();

		auto aGameObject = CFactory::Instance().New<TGameObject>();
		if (aGameObject == nullptr)
		{
			aSession->SetDisconnect();
			aSession->OnAccessEnd();

			LB_ASSERT(aSession->GetState() == CManagedObject::EState::eReturned, "���⿡�� �ݳ��� �Ǿ�� �Ѵ�.");
			return 1;
		}
		aSession->SetGameObject(aGameObject);
		aGameObject->LinkSession(aSession);

		CAcceptor* aAcceptPtr = &pAcceptor;

		pAcceptor.Listen();
		pAcceptor.AcceptAsync(*aSession,
			[this, aSession, aAcceptPtr](const boost::system::error_code& pErr)
		{
			if (pErr.value() != 0)
			{
				aSession->SetDisconnect();
				aSession->OnAccessEnd();
				return;
			}

			ErrCode aErr = aSession->OnAccept();
			if (aErr != 0)
			{
				aSession->SetDisconnect();
				aSession->OnAccessEnd();
				LB_ASSERT(aSession->GetState() == CManagedObject::EState::eReturned, "���⿡�� �ݳ��� �Ǿ�� �Ѵ�.");
				return;
			}

			aSession->OnAccessEnd();
			__SetAccept(*aAcceptPtr);
		});

		return 0;
	}
}