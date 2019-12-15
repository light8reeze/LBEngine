namespace LBNet
{
	inline SAddressInfo::SAddressInfo(char* pIp, unsigned int pPort) : mIp(pIp), mPort(pPort)
	{
	}

	inline SAddressInfo::SAddressInfo(std::string pIp, unsigned int pPort) : mIp(pIp), mPort(pPort)
	{
	}

	inline CConfig::CConfig() : _mThreadCnt(0), _mSessionCnt(2000),
		_mTimerTaskCnt(eSzTimerTask)
	{
		_mThreadCnt = std::thread::hardware_concurrency() * 2;
	}

	inline void CConfig::AddAddress(char* pIP, unsigned int pPort)
	{
		_mAcceptorAddrList.emplace_back(pIP, pPort);
	}

	inline void CConfig::SetThreadCnt(unsigned pThread)
	{
		_mThreadCnt = pThread;
	}

	inline void CConfig::SetSessionCnt(unsigned pSession)
	{
		_mSessionCnt = pSession;
	}

	inline void CConfig::SetTimerTaskCnt(unsigned pTimerTask)
	{
		_mTimerTaskCnt = pTimerTask;
	}

	inline Size CConfig::GetAddressCnt() const
	{
		return static_cast<Size>(_mAcceptorAddrList.size());
	}

	inline const SAddressInfo& CConfig::GetAddress(int pIndex) const
	{
		LB_ASSERT(pIndex < GetAddressCnt(), "Invalid!");

		return _mAcceptorAddrList[pIndex];
	}

	inline unsigned CConfig::GetThreadCnt() const
	{
		return _mThreadCnt;
	}

	inline unsigned CConfig::GetSessionCnt() const
	{
		return _mSessionCnt;
	}

	inline unsigned CConfig::GetTimerTaskCnt() const
	{
		return _mTimerTaskCnt;
	}
}