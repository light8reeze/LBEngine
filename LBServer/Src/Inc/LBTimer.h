/**
	@file	LBTimer.h
	@brief	LBServer�� Ÿ�̸� ���� ���
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
		@brief	        Ÿ�̸� ���� Ŭ����
		@details		boost::asio::system_timer�� ó������ �����ϱ� ���� Ŭ����
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
		@brief	        Ÿ�̸� Ŭ����
		@details		Ư�� �ð� �� �񵿱������� ����� ó���ϴ� Ŭ����
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
			@brief				Ÿ�̸� ���� �Լ�
			@param	THandler	������ �ð��� ������ �Լ��̴�. �Լ��� ���´�(ErrCode, ...)�� �ۼ��ؾ� �Ѵ�.
					TArgs		������ �Լ��� �� ���ڸ���Ʈ.
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