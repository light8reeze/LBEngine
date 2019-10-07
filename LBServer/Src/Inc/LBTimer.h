/**
	@file	LBTimer.h
	@brief	LBServer의 타이머 관련 헤더
	@date	2019-10-06
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBServer.h"
#include "LBLocker.h"
#include <boost/asio/steady_timer.hpp>

namespace LBNet
{
	class CTime;

	/**
		@brief	        타이머 보관 클래스
		@details		boost::asio::system_timer를 처리까지 보관하기 위한 클래스
		@date	        2019-10-07
		@auther         light8reeze(light8reeze@gmail.com)
	*/
	class LBS_EXPORT CTimerStorage
	{
	private:
		using __TimerWorkList = std::map<std::size_t, boost::asio::system_timer>;

	public:
		CTimerStorage() = default;
		~CTimerStorage() = default;

		void AddTimer(std::size_t pKey, boost::asio::system_timer&& pTimer);
		void RemoveTimer(std::size_t pKey);
		
	private:
		__TimerWorkList __mWorkList;
		CSharedMutex	__mMutex;
	};

	/**
		@brief	        타이머 클래스
		@details		특정 시간 후 비동기적으로 명령을 처리하는 클래스
		@date	        2019-10-06
		@auther         light8reeze(light8reeze@gmail.com)
	*/
	class LBS_EXPORT CTimer
	{
	public:
		CTimer();
		CTimer(CTimer&& pTimer);
		CTimer(const CTimer& pTimer) = delete;
		CTimer(const CTime& pTime);

		template<class Rep, class Period>
		CTimer(const std::chrono::duration<Rep, Period>& pTime);
		~CTimer();

		CTimer& operator=(const CTimer&) = delete;

		void SetTime(const CTime& pTime);
		
		template<class Rep, class Period>
		void SetTime(const std::chrono::duration<Rep, Period>& pTime);

		/**
			@brief				타이머 시작 함수
			@param	THandler	설정된 시간에 실행할 함수이다. 함수의 형태는(ErrCode, ...)로 작성해야 한다.
					TArgs		실행할 함수에 들어갈 인자리스트.
		*/
		template<typename THandler, typename... TArgs>
		void Start(THandler&& pHandler, TArgs... pArgs);
		void Cancel();

	private:
		boost::asio::system_timer	__mTimer;

		static CTimerStorage		__mStorage;
	};
}

#include "LBTimer.Inl"