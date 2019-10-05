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
#ifdef _WINDOWS
	/**
		@brief		잠금 클래스(Windows)
		@details	크리티컬 섹션을 이용한 잠금 클래스(윈도우 전용)
		@comments	1. os에 독립적인 std::mutex를 사용하려고 하나 수행시간이 
					짧은 lock에는 mutex가 비효율적이다. 그래서 윈도우에서는 CriticalSection를, 
					리눅스에서는 추후에 pthread_mutex를 이용하여 구현한다.
					2. RAII는 std의 구현된 RAII를 사용한다.(ex : std::unique_lock)
		@date		2019-03-31
		@auther		light8reeze(light8reeze@gmail.com)
	*/
	class LBU_EXPORT CLocker
	{
	public:
		using AutoLock = std::unique_lock<CLocker>;

	public:
		CLocker();
		~CLocker();

		void lock();
		void unlock();
		bool try_lock();

	private:
		CRITICAL_SECTION __mCS;
	};
#endif //_WINDOWS

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