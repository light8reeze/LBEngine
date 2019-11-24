#include "LBTimer.h"
#include "LBIOContext.h"
#include <iostream>

namespace LBNet
{
#pragma region CTimerStorage
	void CTimerStorage::AddTimer(const CTimerKey&& pKey, SystemTimer&& pTimer)
	{
		WriteLock aLock(__mMutex);

		auto aResult = __mWorkList.emplace(std::move(pKey), std::move(pTimer));
		LB_ASSERT(aResult.second == true, "Error!");
	}

	void CTimerStorage::RemoveTimer(const CTimerKey& pKey)
	{
		WriteLock aLock(__mMutex);

		__mWorkList.erase(pKey);
	}
#pragma endregion CTimerStorage

#pragma region CTimer
	CTimerStorage CTimer::__mStorage;

	CTimer::CTimer() : __mTimer(CIOContext::Instance().GetIOContext()), __mTimerKey(), __mPeriod()
	{
	}

	CTimer::CTimer(CTimer&& pTimer) : __mTimer(std::move(pTimer.__mTimer)),
		__mPeriod(std::move(pTimer.__mPeriod))
	{
	}

	CTimer::CTimer(const CTime& pTime) : __mTimer(CIOContext::Instance().GetIOContext(), pTime.GetTimePoint())
	{
	}

	CTimer::~CTimer()
	{
		__mStorage.AddTimer(std::move(__mTimerKey), std::move(__mTimer));
	}

	void CTimer::SetTime(const CTime& pTime)
	{
		__mTimer.expires_at(pTime.GetTimePoint());
	}

	void CTimer::Cancel()
	{
		__mTimer.cancel();
	}
#pragma endregion CTimer
}