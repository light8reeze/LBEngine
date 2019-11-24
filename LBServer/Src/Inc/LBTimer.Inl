namespace LBNet
{
	template<class Rep, class Period>
	CTimer::CTimer(const std::chrono::duration<Rep, Period>& pTime)
		: __mTimer(CIOContext::Instance().GetIOContext(), pTime), __mTimerKey(), __mPeriod(0ms)
	{
	}

	template<class Rep, class Period>
	void CTimer::SetTime(const std::chrono::duration<Rep, Period>& pTime)
	{
		__mTimer.expires_after(pTime);
	}

	template<class Rep, class Period>
	void CTimer::SetPeriod(const std::chrono::duration<Rep, Period>& pTime)
	{
		__mPeriod = std::chrono::duration_cast<Tick>(pTime);
	}

	template<typename THandler, typename... TArgs>
	void CTimer::Start(THandler&& pHandler, TArgs... pArgs)
	{
		__mTimer.async_wait(
			[=](const boost::system::error_code& pErr)
		{
			ErrCode aErr = pErr.value();
			bool aNextExe = pHandler(aErr, pArgs...);

			__mStorage.RemoveTimer(__mTimerKey);

			if (__mPeriod > 0ms && aNextExe == true)
			{
				CTimer aNextTimer(__mPeriod);
				aNextTimer.SetPeriod(__mPeriod);
				aNextTimer.Start(pHandler, pArgs...);
			}
		});
	}
}