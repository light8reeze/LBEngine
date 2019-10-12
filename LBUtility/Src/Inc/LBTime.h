/**
	@file	LBTime.h
	@brief	LBUtillity�� �ð����� ���
	@date	2019-03-16
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBUtility.h"
#include <ctime>

/**
	@brief �����ϴ� OS�� ���� localtime�Լ��� �����Ѵ�.
*/
#ifdef _WINDOWS
	#define LOCALTIME(TM, time) localtime_s((TM), (time))
#elif _LINUX
	#define LOCALTIME(TM, time) localtime_r((time), (TM))
#else
	#error "Define _WINDOWS or _LINUX"
#endif //_WINDOWS

namespace LBNet
{
	/**
		@brief		���� Enum����
		@warning	struct tm�� tm_wday���� ����� �Ѵ�.(0:�Ͽ��� ~ 6:�����)
	*/
	enum class EWeekday
	{
		eSunday = 0,
		eMonday,
		eTuesday,
		eWednesday,
		eThursday,
		eFriday,
		eSaturday
	};

	/**
		@brief		LBUtillity�� �ð� Ŭ����
		@details	Ư�� �ð��� ǥ���ϴ� Ŭ����, std::chrono�� ������� ���� Get, Set�� struct tm�� ������ TimePoint�� �̿��Ѵ�
		@date		2019-03-16
		@auther		light8reeze(light8reeze@gmail.com)
	*/
	class LBU_EXPORT CTime
	{
	private:
		using Clock		= std::chrono::system_clock;
		using TimePoint = Clock::time_point;

	public:
		CTime();
		CTime(const CTime&) = default;
		~CTime() = default;
		
		CTime&	operator=(const CTime&) = default;
		CTime&	operator+=(const CTime& pTime);
		CTime&	operator-=(const CTime& pTime);
		CTime	operator+(const CTime& pTime);
		CTime	operator-(const CTime& pTime);
		
		template<class Rep, class Period>
		CTime&	operator+=(const std::chrono::duration<Rep, Period>& pTime);
		template<class Rep, class Period>
		CTime&	operator-=(const std::chrono::duration<Rep, Period>& pTime);
		template<class Rep, class Period>
		CTime	operator+(const std::chrono::duration<Rep, Period>& pTime);
		template<class Rep, class Period>
		CTime	operator-(const std::chrono::duration<Rep, Period>& pTime);

	public:
		void SetNow();
		void SetYear(int pYear);
		void SetMonth(int pMonth);
		void SetDay(int pDay);
		void SetHour(int pHour);
		void SetMinute(int pMinute);
		void SetSecond(int pSecond);
		void SetTimePoint(TimePoint pTimePoint);

		TimePoint	GetTimePoint() const;
		Tick		ToTick() const;
		TickCount	ToTickCount() const;
		int			GetYear() const;
		int			GetMonth() const;
		int			GetDay() const;
		int			GetHour() const;
		int			GetMinute() const;
		int			GetSecond() const;
		EWeekday	GetWeekday() const;

		static const CTime& GetStartTime();
		static Tick			GetSteadyTick();
		static TickCount	GetSteadyTickCount();
		static Tick			GetSystemTick();
		static TickCount	GetSystemTickCount();

	private:
		void __UpdateFromTimePoint();
		void __UpdateFromLocalTime();

	private:
		static const CTime __mStartTime;

		#pragma warning(disable : 4251)
		TimePoint	__mTimePoint;
		#pragma warning(default : 4251)
		struct tm	__mLocalTime;
	};
}

#include "LBTime.Inl"