#include "LBLocker.h"

namespace LBNet
{
#ifdef _DEBUG
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

		if (aResult)
		{
			__mOwner = std::this_thread::get_id();
		}

		return aResult;
	}

	void CSharedMutex::lock_shared()
	{
		__mMutex.lock_shared();
		DEBUG_CODE(__mOwner = std::this_thread::get_id());
	}

	void CSharedMutex::unlock_shared()
	{
		__mMutex.unlock_shared();
		DEBUG_CODE(__mOwner = std::thread::id());
	}

	bool CSharedMutex::try_lock_shared()
	{
		auto aResult = __mMutex.try_lock_shared();

		if (aResult)
		{
			__mOwner = std::this_thread::get_id();
		}

		return aResult;
	}
#endif //_DEBUG
}