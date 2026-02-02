#include <iostream>

namespace LBNet
{
#pragma region CTimerTask
	template<class Rep, class Period>
	CTimerTask::CTimerTask(const std::chrono::duration<Rep, Period>& pTime)
		: __mTimer(CIOContext::Instance().GetIOContext(), pTime)
	{
	}

	template<class Rep, class Period>
	void CTimerTask::SetTime(const std::chrono::duration<Rep, Period>& pTime)
	{
		__mTimer.expires_after(pTime);
	}

	template<typename THandler, typename... TArgs>
	void CTimerTask::Start(THandler&& pHandler, TArgs... pArgs)
	{
		__mTimer.async_wait([pHandler, pArgs...](const boost::system::error_code& pErr)
		{
			ErrCode aErr = pErr.value();
			pHandler(aErr, pArgs...);
		});
	}
#pragma endregion CTimerTask

#pragma region CTimer
	template<class Rep, class Period, typename THandler, typename... TArgs>
	ErrCode CTimer::Start(const std::chrono::duration<Rep, Period>&& pTime,
		THandler&& pHandler, TArgs... pArgs)
	{
		auto aTask = CFactory::Instance().New<CTimerTask>();
		if (aTask == nullptr)
			return eErrCodeNotEnoughRsc;

		aTask->SetTime(pTime);
		aTask->Start([aTask, pHandler, pArgs...](ErrCode pErr)
		{
			pHandler(pErr, pArgs...);
		});

		return 0;
	}
	template<class Rep, class Period, typename THandler, typename... TArgs>
	ErrCode CTimer::Start(const std::chrono::duration<Rep, Period>& pTime,
		THandler&& pHandler, TArgs... pArgs)
	{
		auto aTask = CFactory::Instance().New<CTimerTask>();
		if (aTask == nullptr)
			return eErrCodeNotEnoughRsc;

		aTask->SetTime(pTime);
		aTask->Start([aTask, pHandler, pArgs...](ErrCode pErr)
		{
			pHandler(pErr, pArgs...);
		});

		return 0;
	}

	template<typename THandler, typename... TArgs>
	ErrCode CTimer::Start(const CTime& pTime, THandler&& pHandler, TArgs... pArgs)
	{
		auto aTask = CFactory::Instance().New<CTimerTask>();
		if (aTask == nullptr)
			return eErrCodeNotEnoughRsc;

		aTask->SetTime(pTime);
		aTask->Start([aTask, pHandler, pArgs...](ErrCode pErr)
		{
			pHandler(pErr, pArgs...);
		});

		return 0;
	}

	template<typename THandler, typename... TArgs>
	ErrCode CTimer::Start(CTimerTask& pTimer, THandler&& pHandler, TArgs... pArgs)
	{
		pTimer.Start([pHandler, pArgs...](ErrCode pErr)
		{
			pHandler(pErr, pArgs...);
		});

		return 0;
	}
#pragma endregion CTimer
}