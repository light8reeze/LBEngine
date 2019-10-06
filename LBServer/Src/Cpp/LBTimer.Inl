namespace LBNet
{
	template<class Rep, class Period>
	CTimer::CTimer(const std::chrono::duration<Rep, Period>& pTime)
		: __mTimer(CIOContext::Instance().GetIOContext(), pTime)
	{
	}

	template<class Rep, class Period>
	void CTimer::SetTime(const std::chrono::duration<Rep, Period>& pTime)
	{
		__mTimer.expires_after(pTime);
	}

	template<typename THandler, typename... TArgs>
	void CTimer::Start(THandler&& pHandler, TArgs... pArgs)
	{
		__mTimer.async_wait(
			[pHandler, pArgs...](const boost::system::error_code& pErr)
		{
			ErrCode aErr = pErr.value();
			pHandler(aErr, pArgs...);
		});
	}
}