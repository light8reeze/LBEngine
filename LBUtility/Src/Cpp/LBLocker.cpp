#include "LBLocker.h"

extern "C" void asm_pause();

namespace LBNet
{
	CLocker::CLocker() : __mIsLock(0)//, __mOwnerThread()
	{
	}

	void CLocker::lock()
	{
		while (!__mIsLock.compare_exchange_strong(aExp, 1))
		{
			//aExp = false;

			asm_pause();
		}

		__mIsLock.store(1);
		//__mOwnerThread.store(std::this_thread::get_id());
	}

	void CLocker::unlock()
	{
		//LB_ASSERT(std::this_thread::get_id() == __mOwnerThread && __mIsLock == true, "Invalid Lock!");
		__mIsLock.store(0);
	}

	bool CLocker::try_lock()
	{
		return !__mIsLock.load();
	}
}