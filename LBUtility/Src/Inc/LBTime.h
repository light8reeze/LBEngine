/**
	@file	LBTime.h
	@brief	LBUtillity의 시간관련 헤더
	@date	2019-03-16
	@auther Light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBUtility.h"
#include <ctime>

/**
	@brief 빌드하는 OS에 맞춰 localtime함수를 정의한다.
*/
#ifdef _WINDOWS
	#define LOCALTIME(TM, time) localtime_s((TM), (time))
#elif _LINUX
	#define LOCALTIME(TM, time) localtime_r((time), (TM))
#endif //_WINDOWS

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
		@todo		duraction litral을 이용한 연산자 구현할것.
		@auther		Light8reeze(light8reeze@gmail.com)
	*/
	class LB_UTILL_EXPORT CTime
	{
	private:
		using TimePoint = std::chrono::system_clock::time_point;

	public:
		CTime();
		CTime(const CTime&) = default;
		~CTime() = default;
		
		CTime&	operator=(const CTime&) = default;
		CTime&	operator+=(const CTime& pTime);
		CTime&	operator-=(const CTime& pTime);
		CTime	operator+(const CTime& pTime);
		CTime	operator-(const CTime& pTime);

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
		Tick		GetTick() const;
		TickLep		GetTickCount() const;
		int			GetYear() const;
		int			GetMonth() const;
		int			GetDay() const;
		int			GetHour() const;
		int			GetMinute() const;
		int			GetSecond() const;
		EWeekday	GetWeekday() const;

		static const CTime& GetStartTime();

	private:
		void UpdateFromTimePoint();
		void UpdateFromLocalTime();

	private:
		static const CTime __mStartTime;

		TimePoint	__mTimePoint;
		struct tm	__mLocalTime;
	};
}