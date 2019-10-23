/**
	@file	LBTimer.h
	@brief	LBServer�� Ÿ�̸� ���� ���
	@date	2019-10-06
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBServer.h"
#include "LBLocker.h"
#include "LBTime.h"
#include <thread>
#include <boost/asio/steady_timer.hpp>

namespace LBNet
{
	class CTime;


	/**
		@brief	        Ÿ�̸� Ű Ŭ����
		@details		Ÿ�̸� ����ҿ� �����ϱ� ���� Ű ��, ������ ID, ��� ƽ���� �����ȴ�.
		@date	        2019-10-07
		@auther         light8reeze(light8reeze@gmail.com)
	*/
	class CTimerKey
	{
	public:
		CTimerKey() : mID(std::this_thread::get_id()), mTick(CTime::GetSystemTickCount())
		{
		}

		bool operator<(const CTimerKey& pRValue) const
		{
			if (mTick == pRValue.mTick)
				return mID < pRValue.mID;
			else
				return mTick < pRValue.mTick;
		}

	public:
		std::thread::id mID;
		TickCount			mTick;
	};

	using SystemTimer = boost::asio::system_timer;

	/**
		@brief	        Ÿ�̸� ���� Ŭ����
		@details		boost::asio::system_timer�� ó������ �����ϱ� ���� Ŭ����
		@date	        2019-10-07
		@auther         light8reeze(light8reeze@gmail.com)
	*/
	class LBS_EXPORT CTimerStorage
	{
	private:
		using __TimerWorkList = std::map<CTimerKey, SystemTimer>;

	public:
		CTimerStorage() = default;
		~CTimerStorage() = default;

		void			AddTimer(const CTimerKey pKey, SystemTimer&& pTimer);
		void			RemoveTimer(const CTimerKey& pKey);

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
		template<class Rep, class Period>
		void SetPeriod(const std::chrono::duration<Rep, Period>& pTime);

		/**
			@brief				Ÿ�̸� ���� �Լ�
			@param	THandler	������ �ð��� ������ �Լ��̴�. �Լ��� ���´� bool(ErrCode, ...)�� �ۼ��ؾ� �Ѵ�.
					TArgs		������ �Լ��� �� ���ڸ���Ʈ.
		*/
		template<typename THandler, typename... TArgs>
		void Start(THandler&& pHandler, TArgs... pArgs);
		void Cancel();

	private:
		SystemTimer		__mTimer;
		CTimerKey		__mTimerKey;
		Tick			__mPeriod;

		static CTimerStorage		__mStorage;
	};
}

#include "LBTimer.Inl"