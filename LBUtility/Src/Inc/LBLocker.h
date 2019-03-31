/**
	@file	LBLocker.h
	@brief	LBUtillity의 잠금관련 헤더
	@date	2019-03-31
	@auther Light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBUtility.h"
#include "LBThread.h"
#include <atomic>

namespace LBNet
{
	/**
		@brief		잠금 클래스
		@details	스핀락 방식을 이용하여 구현한 잠금 클래스<L5>
		@comments	윈도우에는 CriticalSection, SRWLock가 있지만 리눅스에는 유저모드 동기화가 없다. 그렇기 때문에 스핀락방식을 직접 구현한다.
		@date		2019-03-31
		@auther		Light8reeze(light8reeze@gmail.com)
	*/
	class LB_UTILL_EXPORT CLocker
	{
	private:
		using LockFlag		= std::atomic<char>;
		using LockedThread	= std::atomic<CThread::id>;
		
	public:
		CLocker();
		~CLocker() = default;

		void lock();
		void unlock();
		bool try_lock();

	private:
		LockFlag		__mIsLock;
		char aExp = 0;
		//int				__mSpinCount;
		//LockedThread	__mOwnerThread;
	};
}