#include "LBTimer.h"
#include "LBTime.h"
#include "LBIOContext.h"

namespace LBNet
{
#pragma region CTimerStorage
	void CTimerStorage::AddTimer(std::size_t pKey, boost::asio::system_timer&& pTimer)
	{
		WriteLock aLock(__mMutex);

		auto aResult = __mWorkList.emplace(std::move(pKey), std::move(pTimer));
		LB_ASSERT(aResult.second == true, "Error!");
	}

	void CTimerStorage::RemoveTimer(std::size_t pKey)
	{
		WriteLock aLock(__mMutex);

		__mWorkList.erase(pKey);
	}
#pragma endregion CTimerStorage

#pragma region CTimer
	CTimerStorage CTimer::__mStorage;

	CTimer::CTimer() : __mTimer(CIOContext::Instance().GetIOContext())
	{
	}

	CTimer::CTimer(CTimer&& pTimer) : __mTimer(std::move(pTimer.__mTimer))
	{
	}

	CTimer::CTimer(const CTime& pTime) : __mTimer(CIOContext::Instance().GetIOContext(), pTime.GetTimePoint())
	{
	}

	CTimer::~CTimer()
	{
		std::size_t aKey = reinterpret_cast<std::size_t>(this);
		__mStorage.AddTimer(aKey, std::move(__mTimer));
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