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

	template<class Rep, class Period>
	void CTimer::SetPeriod(const std::chrono::duration<Rep, Period>& pTime)
	{
		__mPeriod = std::chrono::duration_cast<Tick>(pTime);
	}

	template<typename THandler, typename... TArgs>
	void CTimer::Start(THandler&& pHandler, TArgs... pArgs)
	{
		__mTimerKey.mID = std::this_thread::get_id();
		__mTimerKey.mTick = CTime::GetSystemTickCount();

		CTimerKey aKey = __mTimerKey;
		Tick aPeriod = __mPeriod;

		__mTimer.async_wait(
			[aKey, aPeriod, pHandler, pArgs...](const boost::system::error_code& pErr)
		{
			ErrCode aErr = pErr.value();
			bool aNextExe = pHandler(aErr, pArgs...);

			__mStorage.RemoveTimer(aKey);

			if (aPeriod > 0ms && aNextExe == true)
			{
				CTimer aNextTimer(aPeriod);
				aNextTimer.Start(pHandler, pArgs...);
			}
		});
	}
}