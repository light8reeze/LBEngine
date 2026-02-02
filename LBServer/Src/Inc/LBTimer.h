/**
	@file	LBTimer.h
	@brief	LBServer의 타이머 관련 모듈
	@date	2019-10-06
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBServer.h"
#include "LBFactory.h"
#include "LBIOContext.h"
#include <boost/asio/steady_timer.hpp>

namespace LBNet
{
	class CTime;

	using SystemTimer = boost::asio::system_timer;

	/**
		@brief	        타이머 태스크 클래스
		@details		특정 시간 후 원하는 동작을 수행하는 클래스
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
			@param	THandler	설정된 시간에 동작할 함수이다. 함수의 첫번째 인자는 (ErrCode, ...)로 작성해야 한다.
					TArgs		동작할 함수의 뒤 인자리스트.
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
			@param	THandler	설정된 시간에 동작할 함수이다. 함수의 형태는 bool(ErrCode, ...)로 작성해야 한다.
					TArgs		동작할 함수의 뒤 인자리스트.
			@warning			팩토리에서 CTimerTask자원을 할당못할경우 eErrCodeNotEnoughRsc에러가 반환된다.
		*/
		template<class Rep, class Period, typename THandler, typename... TArgs>
		static ErrCode Start(const std::chrono::duration<Rep, Period>&& pTime, 
					THandler&& pHandler, TArgs... pArgs);
		template<class Rep, class Period, typename THandler, typename... TArgs>
		static ErrCode Start(const std::chrono::duration<Rep, Period>& pTime,
					THandler&& pHandler, TArgs... pArgs);

		template<typename THandler, typename... TArgs>
		static ErrCode Start(const CTime& pTime, THandler&& pHandler, TArgs... pArgs);

		/**
			@brief				타이머 시작 함수
			@param	THandler	설정된 시간에 동작할 함수이다. 함수의 인자는 (ErrCode, ...)로 작성해야 한다.
					TArgs		동작할 함수의 뒤 인자리스트.
			@warning			해당 함수 사용시 CTimerTask가 설정 시간 이전에 소멸되면 작업이 바로 종료된다.
								사용자가 CTimerTask의 생명을 관리해야 한다.
		*/
		template<typename THandler, typename... TArgs>
		static ErrCode Start(CTimerTask& pTimer, THandler&& pHandler, TArgs... pArgs);
	};
}

#include "LBTimer.Inl"
