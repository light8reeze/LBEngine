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

	template<typename TLocker>
	using ReadLock	= std::shared_lock<TLocker>;
	template<typename TLocker>
	using WriteLock	= std::unique_lock<TLocker>;


	/**
		@brief		Mutex��� ������Ʈ ����
		@details	Mutex��� ������Ʈ ������ ������ ����.
					1. Ŭ�������� LB_LOCKOBJECT(Ŭ������, MutexŸ�Ը�)�� �ִ´�.
					2. ��ü ����� ����Ҷ� {ReadLock ������(���۷���) or WriteLock ������(���۷���)}�� ����Ѵ�.
		@warnning	��ũ�� ��� �Ŀ� �����ڸ� �����Ѵ�.(�������� ��ũ�� �Ʒ��� protected�����ڷ� �νĵȴ�.)

		@param pClass		����� ������Ʈ Ŭ���� Ÿ��
		@param pLockType	����� MutexŬ���� Ÿ��
		@date				2020-05-11
		@auther				light8reeze(light8reeze@gmail.com)
	*/
	#define LB_LOCKOBJECT(pClass, pLockType)		public:\
													using ReadLock	= LBNet::ReadLock<pClass>;\
													using WriteLock = LBNet::WriteLock<pClass>;\
													void lock(){ _mLocker.lock(); }\
													void unlock(){ _mLocker.unlock(); }\
													bool try_lock(){ return _mLocker.try_lock(); }\
													void lock_shared(){ _mLocker.lock_shared(); }\
													void unlock_shared(){ _mLocker.unlock_shared(); }\
													bool try_lock_shared(){ return _mLocker.try_lock(); }\
													const pLockType& GetLocker() const { return _mLocker; }\
													protected:\
													pLockType _mLocker;
}