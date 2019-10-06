/**
	@file	LBLocker.h
	@brief	LBUtillity의 잠금관련 헤더
	@date	2019-03-31
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBUtility.h"
#include <mutex>
#include <shared_mutex>

namespace LBNet
{
	/**
		@brief		뮤텍스 클래스
		@details	std::shared_mutex을 이용한 잠금 클래스
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

#ifdef _DEBUG
		std::thread::id GetOwner() { return __mOwner; }
#endif //_DEBUG

	private:
		#pragma warning(disable : 4251)
		std::shared_mutex __mMutex;
		DEBUG_CODE(std::thread::id	__mOwner{});
		#pragma warning(default : 4251)
	};

	using ReadLock		= std::shared_lock<CSharedMutex>;
	using WriteLock		= std::unique_lock<CSharedMutex>;
}