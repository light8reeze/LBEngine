/**
	@file	LBThread.h
	@brief	LBUtillity의 쓰레드 클래스 정의
	@date	2019-03-16
	@auther Light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBUtility.h"
#include "LBTime.h"
#include <thread>

namespace LBNet
{
	/**
		@file		LBThread.h
		@brief		LBUtillity의 쓰레드 클래스
		@details	std쓰레드를 기반으로 구현한 쓰레드 하위 클래스에서 상속받아 Main을 구현하여 사용한다.
		@date		2019-03-16
		@auther		Light8reeze(light8reeze@gmail.com)
		@todo		추후 Thread관리 클래스 구현시 L1 ~ L3 참고, 컨텍스트 스위칭 구현
	*/
	class LB_UTILL_EXPORT CThread
	{
	public:
		using id = std::thread::id;

	public:
		CThread();
		virtual ~CThread();
		CThread(const CThread& pCopy) = delete;
		CThread& operator=(const CThread& pRvalue) = delete;

		virtual int Initialize();
		int		StartThread();
		int		JoinThread();
		template< class Rep, class Period >
		void	Sleep(const std::chrono::duration<Rep, Period>& pDuration);
		void	SetSwitchingTime(Tick& pTick);
		bool	SetAffinity(int pCpu);
		
		id GetThreadId() const;

	private:
		void ThreadRoutine();
		virtual int Main() = 0;

	protected:
		void	ContextSwitching();

	private:
		std::thread		__mThread;
		int				__mResult;
		TickLep			__mSwitchingPeriod;
		CTime			__mLastSwitchingTime;
	};
}

#include "LBThread.Inl"