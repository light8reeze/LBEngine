#include "LBThread.h"
#ifdef _WINDOWS
#include <Windows.h>
#include <process.h>
#elif _LINUX
#endif //_WINDOWS

namespace LBNet
{
	/**
		@brief CThread의 생성자
	*/
	CThread::CThread() : __mThread(), __mResult(-1), __mSwitchingPeriod(-1), __mLastSwitchingTime()
	{
	}

	/**
		@brief CThread의 소멸자
	*/
	CThread::~CThread()
	{
	}

	/**
		@brief	쓰레드 클래스를 설정하는 함수.
		@return	쓰레드 설정 결과값
	*/
	int CThread::Initialize()
	{
		return 0;
	}

	/**
		@brief	쓰레드 시작하는 함수.
		@return	쓰레드 시작 결과값
	*/
	int CThread::StartThread()
	{
		auto aLpfnThread	= std::bind(&CThread::ThreadRoutine, this);
		__mThread			= std::thread(aLpfnThread);

		return 0;
	}

	/**
		@brief		쓰레드 종료까지 대기하는 함수
		@warning	이 함수를 실행하면 쓰레드가 종료될때까지 block상태가 됩니다.
		@return		쓰레드 실행 결과
	*/
	int CThread::JoinThread()
	{
		if(__mThread.joinable() == true)
			__mThread.join();

		return __mResult;
	}

	/**
		@brief		쓰레드의 ID값을 받는 함수
		@return		쓰레드의 ID값
	*/
	CThread::id CThread::GetThreadId() const
	{
		return __mThread.get_id();
	}

	/**
		@brief		쓰레드가 실행될때 실행하는 루틴함수
	*/
	void CThread::ThreadRoutine()
	{
		LB_ASSERT(GetThreadId() == std::this_thread::get_id(), "Invalid Thread!");
		__mResult = Main();
	}

	/**
		@brief			쓰레드의 컨텍스트 스위칭 주기를 설정하는 함수
		@praram Tick	설정할 컨텍스트 스위칭 주기(ms)
	*/
	void CThread::SetSwitchingTime(Tick& pTick)
	{
		__mSwitchingPeriod = pTick.count();
	}

	/**
		@brief			쓰레드가 실행될 CPU를 지정한다.
		@details		std쓰레드의 affinity는 각 OS에 맞게 직접 구현해야 한다 때문에 OS에 종속적이다.
						윈도우의 경우 윈도우 쓰레드를 사용하여 지정하고, 리눅스의 경우 pthread를 이용하여 지정한다.<L1>
		@warning		_WINDOWS매크로, _LINUX매크로가 둘다 미정의시 에러가 발생한다.
		@todo			Linux모드 구현
		@param unsigned int	지정할 Cpu의 번호
		@return bool	쓰레드의 CPU지정 성공 여부
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
		@brief		컨텍스트 스위칭을 실행하는 함수
		@warning	1. 컨텍스트 스위칭을 하려면 하위 쓰레드 클래스에서 Main내에 직접 함수를 실행해야 한다.
		@warning	2. 스레드를 1ms를 정지 시키나 정확히 1ms가 아닐수도 있다.
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