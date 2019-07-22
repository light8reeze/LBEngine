#include "LBLocker.h"
#include <iostream>

extern "C" void LBPause();

namespace LBNet
{
#ifdef _WINDOWS
#pragma region CLocker
	CLocker::CLocker() : __mCS()
	{
		if (FALSE == ::InitializeCriticalSectionAndSpinCount(&__mCS, 1024))
			LB_ASSERT(0, "Critical Error!");
	}

	CLocker::~CLocker()
	{
		::DeleteCriticalSection(&__mCS);
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
#pragma endregion CLocker
#endif //_WINDOWS

#pragma region CSharedMutex
	CSharedMutex::CSharedMutex() : __mMutex()
	{
	}

	void CSharedMutex::lock()
	{
		__mMutex.lock();
		DEBUG_CODE(__mOwner = std::this_thread::get_id());
	}

	void CSharedMutex::unlock()
	{
		__mMutex.unlock();
		DEBUG_CODE(__mOwner = std::thread::id());
	}

	bool CSharedMutex::try_lock()
	{
		auto aResult = __mMutex.try_lock();

		#ifdef _DEBUG
		if (aResult)
		{
			__mOwner = std::this_thread::get_id();
		}
		#endif //_DEBUG

		return aResult;
	}
#pragma endregion CSharedMutex
}