#include "LBThread.h"

namespace LBNet
{
	/**
		@brief CThread의 생성자
	*/
	CThread::CThread() : __mThread(), __mResult(-1), __mSwitchingTime(0), __mLastSwitchingTime()
	{
		__mLastSwitchingTime = std::chrono::system_clock::now();
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
		auto alpfnThread = std::bind(&CThread::ThreadRoutine, this);
		__mThread			= std::thread(alpfnThread);

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
		__mResult = Main();
	}
}