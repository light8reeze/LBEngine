#include "LBLocker.h"

extern "C" void LBPause();

#ifdef _WINDOWS
namespace LBNet
{
	CLocker::CLocker() : __mCS()
	{
		if (FALSE == ::InitializeCriticalSectionAndSpinCount(&__mCS, 1024))
			LB_ASSERT(0, "Critical Error!");
	}

	void CLocker::lock()
	{
		::EnterCriticalSection(&__mCS);
	}

	void CLocker::unlock()
	{
		::LeaveCriticalSection(&__mCS);
	}

	bool CLocker::try_lock()
	{
		return ::TryEnterCriticalSection(&__mCS);
	}
}

#endif //_WINDOWS