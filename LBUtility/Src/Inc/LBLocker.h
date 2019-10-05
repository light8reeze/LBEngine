/**
	@file	LBLocker.h
	@brief	LBUtillity�� ��ݰ��� ���
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
		@brief		��� Ŭ����(Windows)
		@details	ũ��Ƽ�� ������ �̿��� ��� Ŭ����(������ ����)
		@comments	1. os�� �������� std::mutex�� ����Ϸ��� �ϳ� ����ð��� 
					ª�� lock���� mutex�� ��ȿ�����̴�. �׷��� �����쿡���� CriticalSection��, 
					������������ ���Ŀ� pthread_mutex�� �̿��Ͽ� �����Ѵ�.
					2. RAII�� std�� ������ RAII�� ����Ѵ�.(ex : std::unique_lock)
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
		@brief		���ؽ� Ŭ����
		@details	std::shared_mutex�� �̿��� ��� Ŭ����
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