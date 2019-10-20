/**
	@file	LBLocker.h
	@brief	LBUtillity�� ��ݰ��� ���
	@date	2019-03-31
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBUtility.h"
#include <shared_mutex>

namespace LBNet
{
#ifdef _DEBUG
	/**
		@brief		���ؽ� Ŭ����
		@details	std::shared_mutex�� �̿��� ��� Ŭ����(����� ��忡���� ���)
		@comments	shared_lock, unique_lock�� �̿��Ͽ� Read, Write�� ������ ���� ����
		@date		2019-07-20
		@auther		light8reeze(light8reeze@gmail.com)
	*/
	class LBU_EXPORT CSharedMutex
	{
	public:
		CSharedMutex();
		~CSharedMutex() = default;

		void lock();
		void unlock();
		bool try_lock();
		void lock_shared();
		void unlock_shared();
		bool try_lock_shared();

		std::thread::id GetOwner() { return __mOwner; }

	private:
		#pragma warning(disable : 4251)
		std::shared_mutex __mMutex;
		DEBUG_CODE(std::thread::id	__mOwner{});
		#pragma warning(default : 4251)
	};
#else
	using CSharedMutex	= std::shared_mutex;
#endif //_DEBUG

	using ReadLock		= std::shared_lock<CSharedMutex>;
	using WriteLock		= std::unique_lock<CSharedMutex>;
}