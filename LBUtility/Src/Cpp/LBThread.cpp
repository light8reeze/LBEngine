#include "LBThread.h"
#ifdef _WINDOWS
#include <Windows.h>
#include <process.h>
#elif _LINUX
#endif //_WINDOWS

namespace LBNet
{
	/**
		@brief CThread�� ������
	*/
	CThread::CThread() : __mThread(), __mResult(-1), __mSwitchingPeriod(-1), __mLastSwitchingTime()
	{
	}

	/**
		@brief CThread�� �Ҹ���
	*/
	CThread::~CThread()
	{
	}

	/**
		@brief	������ Ŭ������ �����ϴ� �Լ�.
		@return	������ ���� �����
	*/
	int CThread::Initialize()
	{
		return 0;
	}

	/**
		@brief	������ �����ϴ� �Լ�.
		@return	������ ���� �����
	*/
	int CThread::StartThread()
	{
		auto aLpfnThread	= std::bind(&CThread::ThreadRoutine, this);
		__mThread			= std::thread(aLpfnThread);

		return 0;
	}

	/**
		@brief		������ ������� ����ϴ� �Լ�
		@warning	�� �Լ��� �����ϸ� �����尡 ����ɶ����� block���°� �˴ϴ�.
		@return		������ ���� ���
	*/
	int CThread::JoinThread()
	{
		if(__mThread.joinable() == true)
			__mThread.join();

		return __mResult;
	}

	/**
		@brief		�������� ID���� �޴� �Լ�
		@return		�������� ID��
	*/
	CThread::id CThread::GetThreadId() const
	{
		return __mThread.get_id();
	}

	/**
		@brief		�����尡 ����ɶ� �����ϴ� ��ƾ�Լ�
	*/
	void CThread::ThreadRoutine()
	{
		LB_ASSERT(GetThreadId() == std::this_thread::get_id(), "Invalid Thread!");
		__mResult = Main();
	}

	/**
		@brief			�������� ���ؽ�Ʈ ����Ī �ֱ⸦ �����ϴ� �Լ�
		@praram Tick	������ ���ؽ�Ʈ ����Ī �ֱ�(ms)
	*/
	void CThread::SetSwitchingTime(Tick& pTick)
	{
		__mSwitchingPeriod = pTick.count();
	}

	/**
		@brief			�����尡 ����� CPU�� �����Ѵ�.
		@details		std�������� affinity�� �� OS�� �°� ���� �����ؾ� �Ѵ� ������ OS�� �������̴�.
						�������� ��� ������ �����带 ����Ͽ� �����ϰ�, �������� ��� pthread�� �̿��Ͽ� �����Ѵ�.<L1>
		@warning		_WINDOWS��ũ��, _LINUX��ũ�ΰ� �Ѵ� �����ǽ� ������ �߻��Ѵ�.
		@todo			Linux��� ����
		@param unsigned int	������ Cpu�� ��ȣ
		@return bool	�������� CPU���� ���� ����
	*/
	bool CThread::SetAffinity(unsigned int pCpu)
	{
		LB_ASSERT(pCpu < std::thread::hardware_concurrency(), "Invalid Cpu Number!");
		
		#ifdef _WINDOWS
		HANDLE aNativeHandle = static_cast<HANDLE>(__mThread.native_handle());
		DWORD_PTR aResult = ::SetThreadAffinityMask(aNativeHandle, 1i64 << pCpu);
		
		if (ERROR_INVALID_PARAMETER == aResult)
			return false;

		#elif _LINUX
		#else
			#error define OS _WINDOWS or _LINUX only
		#endif //_WINDOWS
		return true;
	}

	/**
		@brief		���ؽ�Ʈ ����Ī�� �����ϴ� �Լ�
		@warning	1. ���ؽ�Ʈ ����Ī�� �Ϸ��� ���� ������ Ŭ�������� Main���� ���� �Լ��� �����ؾ� �Ѵ�.
		@warning	2. �����带 1ms�� ���� ��Ű�� ��Ȯ�� 1ms�� �ƴҼ��� �ִ�.
	*/
	void CThread::ContextSwitching()
	{
		CTime aNowTime = std::move(aNowTime - __mLastSwitchingTime);
		if (__mSwitchingPeriod != -1 && __mSwitchingPeriod <= aNowTime.GetTickCount())
		{
			std::this_thread::sleep_for(1ms);
			__mLastSwitchingTime.SetNow();
		}
	}
}