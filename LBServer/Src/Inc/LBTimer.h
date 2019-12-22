/**
	@file	LBTimer.h
	@brief	LBServer�� Ÿ�̸� ���� ���
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
		@brief	        Ÿ�̸� �½�ũ Ŭ����
		@details		Ư�� �ð� �� ������ ����� �����ϴ� Ŭ����
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
			@brief				Ÿ�̸� ���� �Լ�
			@param	THandler	������ �ð��� ������ �Լ��̴�. �Լ��� ���� ���´� (ErrCode, ...)�� �ۼ��ؾ� �Ѵ�.
					TArgs		������ �Լ��� �� ���ڸ���Ʈ.
		*/
		template<typename THandler, typename... TArgs>
		void Start(THandler&& pHandler, TArgs... pArgs);

	private:
		#pragma warning(disable : 4251)
		SystemTimer		__mTimer;
		#pragma warning(default : 4251)
	};

	/**
		@brief	        Ÿ�̸� Ŭ����
		@details		Ÿ�̸� �۾� ó�� Ŭ����
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
			@brief				Ÿ�̸� ���� �Լ�
			@param	THandler	������ �ð��� ������ �Լ��̴�. �Լ��� ���´� bool(ErrCode, ...)�� �ۼ��ؾ� �Ѵ�.
					TArgs		������ �Լ��� �� ���ڸ���Ʈ.
			@warning			���丮���� CTimerTask�ڿ��� �����Ұ�� eErrCodeNotEnoughRsc������ ��ȯ�ȴ�.
		*/
		template<class Rep, class Period, typename THandler, typename... TArgs>
		static ErrCode Start(const std::chrono::duration<Rep, Period>& pTime, 
					THandler&& pHandler, TArgs... pArgs);

		template<typename THandler, typename... TArgs>
		static ErrCode Start(const CTime& pTime, THandler&& pHandler, TArgs... pArgs);

		/**
			@brief				Ÿ�̸� ���� �Լ�
			@param	THandler	������ �ð��� ������ �Լ��̴�. �Լ��� ���ڴ� (ErrCode, ...)�� �ۼ��ؾ� �Ѵ�.
					TArgs		������ �Լ��� �� ���ڸ���Ʈ.
			@warning			���� �Լ� ���� CTimerTask�� ���� �ð� ������ �Ҹ�Ǹ� �۾��� �ٷ� ����ȴ�.
								����ڰ� CTimerTask�� ������ �����ؾ� �Ѵ�.
		*/
		template<typename THandler, typename... TArgs>
		static ErrCode Start(CTimerTask& pTimer, THandler&& pHandler, TArgs... pArgs);
	};
}

#include "LBTimer.Inl"