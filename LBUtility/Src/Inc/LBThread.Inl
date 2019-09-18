#pragma once

namespace LBNet
{
	/**
		@brief												쓰레드를 특정 시간동안 정지하는 함수
		@praram const std::chrono::duration<Rep, Period>&	정지시킬 시간 chrono_literal로 사용한다(ex : 1s)
	*/
	template< class Rep, class Period >
	inline void CThread::Sleep(const std::chrono::duration<Rep, Period>& pDuration)
	{
		std::this_thread::sleep_for(pDuration);
	}


	/**
		@brief	쓰레드 시작하는 함수.
		@param	쓰레드 실행 함수.
		@return	쓰레드 시작 결과값
	*/
	template<typename TFunc>
	int CThread::StartThread(TFunc&& pFunc)
	{
		__mThread = std::thread(pFunc);

		return 0;
	}
}