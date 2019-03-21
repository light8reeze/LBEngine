/**
	@file	LBThread.h
	@brief	LBUtillity�� ������ Ŭ���� ����
	@date	2019-03-16
	@auther Light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBUtility.h"
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
	class CThread
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
		template<class Rep, class Period>
		void	Sleep(const std::chrono::duration<Rep, Period>& pDuration);
		void	ContextSwitching();
		void	SetSwitchingTime(Tick pTick);
		
		id GetThreadId() const;

	private:
		void ThreadRoutine();
		virtual int Main() = 0;

	private:
		std::thread								__mThread;
		int										__mResult;
		Tick									__mSwitchingTime;
		std::chrono::system_clock::time_point	__mLastSwitchingTime;
	};
}

#include "LBThread.Inl"