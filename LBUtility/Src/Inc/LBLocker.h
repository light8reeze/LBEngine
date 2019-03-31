/**
	@file	LBLocker.h
	@brief	LBUtillity�� ��ݰ��� ���
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
		@brief		��� Ŭ����
		@details	���ɶ� ����� �̿��Ͽ� ������ ��� Ŭ����<L5>
		@comments	�����쿡�� CriticalSection, SRWLock�� ������ ���������� ������� ����ȭ�� ����. �׷��� ������ ���ɶ������ ���� �����Ѵ�.
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