#include "LBLocker.h"
#include <iostream>

extern "C" void LBPause();

namespace LBNet
{
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
}