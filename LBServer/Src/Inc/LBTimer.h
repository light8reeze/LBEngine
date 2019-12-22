/**
	@file	LBTimer.h
	@brief	LBServer의 타이머 관련 헤더
	@date	2019-10-06
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBServer.h"
#include "LBFactory.h"
#include <boost/asio/steady_timer.hpp>

namespace LBNet
{
	class CTime;

	using SystemTimer = boost::asio::system_timer;

	/**
		@brief	        타이머 태스크 클래스
		@details		특정 시간 후 실행할 명령을 저장하는 클래스
		@date	        2019-10-06
		@auther         light8reeze(light8reeze@gmail.com)
	*/
	class LBS_EXPORT CTimerTask
	{
	public:
		CTimerTask();
		CTimerTask(CTimerTask&& pTimer);
		CTimerTask(const CTimerTask& pTimer) = delete;
		CTimerTask(const CTime& pTime);

		template<class Rep, class Period>
		CTimerTask(const std::chrono::duration<Rep, Period>& pTime);
		~CTimerTask();

		CTimerTask& operator=(const CTimerTask&) = delete;

		void SetTime(const CTime& pTime);

		template<class Rep, class Period>
		void SetTime(const std::chrono::duration<Rep, Period>& pTime);

		/**
			@brief				타이머 시작 함수
			@param	THandler	설정된 시간에 실행할 함수이다. 함수의 인자 형태는 (ErrCode, ...)로 작성해야 한다.
					TArgs		실행할 함수에 들어갈 인자리스트.
		*/
		template<typename THandler, typename... TArgs>
		void Start(THandler&& pHandler, TArgs... pArgs);

	private:
		#pragma warning(disable : 4251)
		SystemTimer		__mTimer;
		#pragma warning(default : 4251)
	};

	/**
		@brief	        타이머 클래스
		@details		타이머 작업 처리 클래스
		@date	        2019-12-15
		@auther         light8reeze(light8reeze@gmail.com)
	*/
	class CTimer
	{
	private:
		CTimer() = default;

	public:
		~CTimer() = default;

		/**
			@brief				타이머 시작 함수
			@param	THandler	설정된 시간에 실행할 함수이다. 함수의 형태는 bool(ErrCode, ...)로 작성해야 한다.
					TArgs		실행할 함수에 들어갈 인자리스트.
			@warning			팩토리에서 CTimerTask자원이 부족할경우 eErrCodeNotEnoughRsc에러가 반환된다.
		*/
		template<class Rep, class Period, typename THandler, typename... TArgs>
		static ErrCode Start(const std::chrono::duration<Rep, Period>& pTime, 
					THandler&& pHandler, TArgs... pArgs);

		template<typename THandler, typename... TArgs>
		static ErrCode Start(const CTime& pTime, THandler&& pHandler, TArgs... pArgs);

		/**
			@brief				타이머 시작 함수
			@param	THandler	설정된 시간에 실행할 함수이다. 함수의 인자는 (ErrCode, ...)로 작성해야 한다.
					TArgs		실행할 함수에 들어갈 인자리스트.
			@warning			다음 함수 사용시 CTimerTask가 설정 시간 이전에 소멸되면 작업이 바로 실행된다.
								사용자가 CTimerTask를 별도로 보관해야 한다.
		*/
		template<typename THandler, typename... TArgs>
		static ErrCode Start(CTimerTask& pTimer, THandler&& pHandler, TArgs... pArgs);
	};
}

#include "LBTimer.Inl"