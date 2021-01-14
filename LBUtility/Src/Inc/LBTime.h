/**
	@file	LBTime.h
	@brief	LBUtillity의 시간관련 헤더
	@date	2019-03-16
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBUtility.h"
#include <ctime>

/**
	@brief 빌드하는 OS에 맞춰 localtime함수를 정의한다.
*/
#ifdef _WIN32
	#define LOCALTIME(TM, time) localtime_s((TM), (time))
#elif __linux__
	#define LOCALTIME(TM, time) localtime_r((time), (TM))
#endif //_WIN32

namespace LBNet
{
	/**
		@brief		요일 Enum정의
		@warning	struct tm의 tm_wday값과 맞춰야 한다.(0:일요일 ~ 6:토요일)
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
		@brief		LBUtillity의 시간 클래스
		@details	특정 시간을 표현하는 클래스, std::chrono를 기반으로 구현 Get, Set은 struct tm을 증감은 TimePoint를 이용한다
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
