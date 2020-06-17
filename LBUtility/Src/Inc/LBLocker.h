/**
	@file	LBLocker.h
	@brief	LBUtillity의 잠금관련 헤더
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
		@brief		뮤텍스 클래스
		@details	std::shared_mutex을 이용한 잠금 클래스(디버그 모드에서만 사용)
		@comments	shared_lock, unique_lock를 이용하여 Read, Write락 구현을 위해 개발
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
		@brief		Mutex사용 오브젝트 지정
		@details	Mutex사용 오브젝트 사용법은 다음과 같다.
					1. 클래스내에 LB_LOCKOBJECT(클래스명, Mutex타입명)을 넣는다.
					2. 객체 잠금을 사용할때 {ReadLock 변수명(레퍼런스) or WriteLock 변수명(레퍼런스)}로 사용한다.
		@warnning	매크로 사용 후에 접근자를 지정한다.(미지정시 매크로 아래로 protected접근자로 인식된다.)

		@param pClass		등록할 오브젝트 클래스 타입
		@param pLockType	등록할 Mutex클래스 타입
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