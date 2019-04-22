/**
	@file	LBLocker.h
	@brief	LBUtillity�� ��ݰ��� ���
	@date	2019-03-31
	@auther Light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBUtility.h"
#include "LBThread.h"
#include <mutex>

#ifdef _WINDOWS
namespace LBNet
{
	/**
		@brief		��� Ŭ����(Windows)
		@details	ũ��Ƽ�� ������ �̿��� ��� Ŭ����(������ ����)
		@comments	1. os�� �������� std::mutex�� ����Ϸ��� �ϳ� ����ð��� 
					ª�� lock���� mutex�� ��ȿ�����̴�. �׷��� �����쿡���� CriticalSection��, 
					������������ ���Ŀ� ���ɶ��� �̿��Ͽ� �����Ѵ�.
					2. RAII�� std�� ������ RAII�� ����Ѵ�.(ex : std::unique_lock)
		@date		2019-03-31
		@auther		Light8reeze(light8reeze@gmail.com)
	*/
	class LB_UTILL_EXPORT CLocker
	{
	public:
		CLocker();
		~CLocker() = default;

		void lock();
		void unlock();
		bool try_lock();

	private:
		CRITICAL_SECTION __mCS;
	};
}
#endif //_WINDOWS