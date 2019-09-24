namespace LBNet
{
	template<typename TGameObject>
	CGameServer<TGameObject>::CGameServer() : _mThreadCnt(0), _mMaxSession(100), 
		__mThreadList(), __mAcceptorList()
	{
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
		__mAcceptorList.push_back(aAcceptor);
	}

	template<typename TGameObject>
	void CGameServer<TGameObject>::AddAcceptor(unsigned short pPort)
	{
		CAcceptor aAcceptor;
		aAcceptor.Bind(pPort);
		__mAcceptorList.push_back(aAcceptor);
	}

	template<typename TGameObject>
	void CGameServer<TGameObject>::SetThreadCount(unsigned int pThread)
	{
		_mThreadCnt = (pThread == 0)? 
			std::thread::hardware_concurrency() * 2 : 
			pThread;
	}

	template<typename TGameObject>
	void CGameServer<TGameObject>::SetSessionMax(unsigned int pSession)
	{
		_mMaxSession = pSession;
	}

	template<typename TGameObject>
	unsigned int CGameServer<TGameObject>::GetThreadCount()
	{
		return _mThreadCnt;
	}

	template<typename TGameObject>
	unsigned int CGameServer<TGameObject>::GetAcceptorCount()
	{
		return static_cast<unsigned int>(__mAcceptorList.size());
	}

	template<typename TGameObject>
	unsigned int CGameServer<TGameObject>::GetSessionMax()
	{
		return _mMaxSession;
	}
}