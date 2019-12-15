#include "LBTimer.h"
#include "LBTime.h"
#include "LBIOContext.h"

namespace LBNet
{
	CTimerTask::CTimerTask() : __mTimer(CIOContext::Instance().GetIOContext())
	{
	}

	CTimerTask::CTimerTask(CTimerTask&& pTimer) : __mTimer(std::move(pTimer.__mTimer))
	{
	}

	CTimerTask::CTimerTask(const CTime& pTime) : __mTimer(CIOContext::Instance().GetIOContext(), pTime.GetTimePoint())
	{
	}

	CTimerTask::~CTimerTask()
	{
	}

	void CTimerTask::SetTime(const CTime& pTime)
	{
		__mTimer.expires_at(pTime.GetTimePoint());
	}
}