#pragma once

namespace LBNet
{
	/**
		@brief												쓰레드를 특정 시간동안 정지하는 함수
		@praram const std::chrono::duration<Rep, Period>&	정지시킬 시간 chrono_literal로 사용한다(ex : 1s)
	*/
	template<typename TDuration>
	inline void CThread::Sleep(const TDuration& pDuration)
	{
		std::this_thread::sleep_for(pDuration);
	}
}