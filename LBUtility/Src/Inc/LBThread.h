/**
	@file	LBThread.h
	@brief	LBUtillity�� ������ Ŭ���� ����
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
		@brief		LBUtillity�� ������ Ŭ����
		@details	std�����带 ������� ������ ������ ���� Ŭ�������� ��ӹ޾� Main�� �����Ͽ� ����Ѵ�.
		@date		2019-03-16
		@auther		Light8reeze(light8reeze@gmail.com)
		@todo		���� Thread���� Ŭ���� ������ L1 ~ L3 ����, ���ؽ�Ʈ ����Ī ����
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