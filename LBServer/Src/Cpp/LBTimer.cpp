#include "LBTimer.h"
#include "LBTime.h"
#include "LBIOContext.h"

namespace LBNet
{
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
	}

	void CTimer::SetTime(const CTime& pTime)
	{
		__mTimer.expires_at(pTime.GetTimePoint());
	}

	void CTimer::Cancel()
	{
		__mTimer.cancel();
	}
}