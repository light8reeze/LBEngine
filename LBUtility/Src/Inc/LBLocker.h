/**
	@file	LBLocker.h
	@brief	LBUtillity의 잠금관련 헤더
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
		@brief		잠금 클래스(Windows)
		@details	크리티컬 섹션을 이용한 잠금 클래스(윈도우 전용)
		@comments	1. os에 독립적인 std::mutex를 사용하려고 하나 수행시간이 
					짧은 lock에는 mutex가 비효율적이다. 그래서 윈도우에서는 CriticalSection를, 
					리눅스에서는 추후에 스핀락을 이용하여 구현한다.
					2. RAII는 std의 구현된 RAII를 사용한다.(ex : std::unique_lock)
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