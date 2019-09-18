/**
	@file	LBThread.h
	@brief	LBUtillity�� ������ Ŭ���� ����
	@date	2019-03-16
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBUtility.h"
#include "LBTime.h"
#include <thread>

namespace LBNet
{
	/**
		@brief		������ Ŭ����
		@details	std�����带 ������� ������ ������ ���� Ŭ�������� ��ӹ޾� Main�� �����Ͽ� ����Ѵ�.
		@date		2019-03-16
		@auther		light8reeze(light8reeze@gmail.com)
		@todo		���� Thread���� Ŭ���� ������ L1 ~ L3 ����, ���ؽ�Ʈ ����Ī ����
					�ش� Ŭ���� ����ϴ� ���� �����(Affinity��� �̿ܿ� Ŭ���� ���� �ǹ̰� ����)
	*/
	class LBU_EXPORT CThread
	{
	public:
		using id = std::thread::id;

	public:
		CThread();
		~CThread();
		CThread(const CThread& pCopy) = delete;
		CThread& operator=(const CThread& pRvalue) = delete;

		virtual int Initialize();
		template<typename TFunc>
		int		StartThread(TFunc&& pFunc);
		int		JoinThread();
		template< class Rep, class Period >
		void	Sleep(const std::chrono::duration<Rep, Period>& pDuration);
		void	SetSwitchingTime(Tick& pTick);
		bool	SetAffinity(unsigned int pCpu);
		
		id GetThreadId() const;

	protected:
		void	ContextSwitching();

	private:
		#pragma warning(disable : 4251)
		std::thread		__mThread;
		#pragma warning(default : 4251)
		int				__mResult;
		RawTick			__mSwitchingPeriod;
		CTime			__mLastSwitchingTime;
	};
}

#include "LBThread.Inl"