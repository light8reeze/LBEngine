#pragma once

namespace LBNet
{
	/**
		@brief		CTime의 생성자
		@details	시간을 현재 시간으로 설정한다.
	*/
	inline CTime::CTime() : __mTimePoint(), __mLocalTime()
	{
		SetNow();
	}

	/**
		@brief		CTime의 +=연산자
	*/
	inline CTime& CTime::operator+=(const CTime& pTime)
	{
		__mTimePoint += pTime.GetTimePoint().time_since_epoch();
		UpdateFromTimePoint();

		return (*this);
	}

	/**
		@brief		CTime의 -=연산자
	*/
	inline CTime& CTime::operator-=(const CTime& pTime)
	{
		__mTimePoint -= pTime.GetTimePoint().time_since_epoch();
		UpdateFromTimePoint();

		return (*this);
	}

	/**
		@brief		CTime의 +연산자
	*/
	inline CTime CTime::operator+(const CTime& pTime)
	{
		CTime aTime;
		TimePoint point = __mTimePoint + pTime.GetTimePoint().time_since_epoch();
		aTime.SetTimePoint(std::move(point));

		return aTime;
	}

	/**
		@brief		CTime의 -연산자
	*/
	inline CTime CTime::operator-(const CTime& pTime)
	{
		CTime time;
		TimePoint point = __mTimePoint - pTime.GetTimePoint().time_since_epoch();
		time.SetTimePoint(std::move(point));

		return time;
	}

	/**
		@brief 시간을 현재 시간으로 설정하는 함수
	*/
	inline void CTime::SetNow()
	{
		using namespace std::chrono;
		__mTimePoint	= system_clock::now();
		time_t time		= std::move(system_clock::to_time_t(__mTimePoint));
		
		::LOCALTIME(&__mLocalTime, &time);
		__mLocalTime.tm_year += 1900;
	}

	/**
		@brief 연도를 설정하는 함수
		@param int pYear 설정할 연도
	*/
	inline void CTime::SetYear(int pYear)
	{
		__mLocalTime.tm_year = pYear;
		UpdateFromLocalTime();
	}

	/**
		@brief 월을 설정하는 함수
		@param int pMonth 설정할 월
	*/
	inline void CTime::SetMonth(int pMonth)
	{
		LB_ASSERT(pMonth >= 0 && pMonth < 12, "Invalid Value!");

		__mLocalTime.tm_mon = pMonth;
		UpdateFromLocalTime();
	}

	/**
		@brief 일을 설정하는 함수
		@param int pDay 설정할 일
	*/
	inline void CTime::SetDay(int pDay)
	{
		LB_ASSERT(pDay >= 0 && pDay <= 31, "Invalid Value!");

		__mLocalTime.tm_mday = pDay;
		UpdateFromLocalTime();
	}

	/**
		@brief 시간을 설정하는 함수
		@param int pHour 설정할 시간
	*/
	inline void CTime::SetHour(int pHour)
	{
		LB_ASSERT(pHour >= 0 && pHour <= 24, "Invalid Value!");

		__mLocalTime.tm_hour = pHour;
		UpdateFromLocalTime();
	}

	/**
		@brief 분을 설정하는 함수
		@param int pMoinute 설정할 분
	*/
	inline void CTime::SetMinute(int pMinute)
	{
		LB_ASSERT(pMinute >= 0 && pMinute <= 60, "Invalid Value!");

		__mLocalTime.tm_min = pMinute;
		UpdateFromLocalTime();
	}

	/**
		@brief 초를 설정하는 함수
		@param int pSecond 설정할 초
	*/
	inline void CTime::SetSecond(int pSecond)
	{
		LB_ASSERT(pSecond >= 0 && pSecond <= 60, "Invalid Value!");

		__mLocalTime.tm_sec = pSecond;
		UpdateFromLocalTime();
	}

	/**
		@brief TimePoint를 설정하는 함수
		@param TimePoint pTimePoint 설정할 TimePoint
	*/
	inline void CTime::SetTimePoint(TimePoint pTimePoint)
	{
		__mTimePoint = pTimePoint;
		UpdateFromTimePoint();
	}

	/**
		@brief TimePoint를 반환하는 함수
	*/
	inline CTime::TimePoint CTime::GetTimePoint() const
	{
		return __mTimePoint;
	}

	/**
		@brief			서버의 시간 틱을 구하는 함수
		@details		서버의 틱은 시간을 ms단위로 반환한다.
		@return	Tick	서버의 시간 틱duration(ms)
	*/
	inline Tick CTime::GetTick() const
	{
		return std::chrono::duration_cast<Tick>(__mTimePoint.time_since_epoch());
	}

	/**
		@brief			서버의 시간 틱을 구하는 함수
		@details		서버의 틱은 경과한 시간을 ms단위로 반환한다.
		@return	Tick	서버의 시간 틱TickLep(ms)
	*/
	inline TickLep CTime::GetTickCount() const
	{
		return std::chrono::duration_cast<Tick>(__mTimePoint.time_since_epoch()).count();
	}

	/**
		@brief	연도를 반환는 함수
		@return 연도값
	*/
	inline int CTime::GetYear() const
	{
		return __mLocalTime.tm_year;
	}

	/**
		@brief 월을 반환하는 함수
		@return 월
	*/
	inline int CTime::GetMonth() const
	{
		return __mLocalTime.tm_mon;
	}

	/**
		@brief 일을 반환하는 함수
		@return 일
	*/
	inline int CTime::GetDay() const
	{
		return __mLocalTime.tm_mday;
	}

	/**
		@brief	시간을 반환하는 함수
		@return 시간
	*/
	inline int CTime::GetHour() const
	{
		return __mLocalTime.tm_hour;
	}

	/**
		@brief	분을 반환하는 함수
		@return 분
	*/
	inline int CTime::GetMinute() const
	{
		return __mLocalTime.tm_min;
	}

	/**
		@brief	초를 반환하는 함수
		@return 초
	*/
	inline int CTime::GetSecond() const
	{
		return __mLocalTime.tm_sec;
	}

	/**
		@brief		요일을 반환하는 함수
		@details	범위는 일요일(0) ~ 토요일(6)이다
		@return		요일
	*/
	inline EWeekday CTime::GetWeekday() const
	{
		LB_ASSERT(__mLocalTime.tm_wday >= 0 && __mLocalTime.tm_wday < 7, "Invalid Weekday");
		return static_cast<EWeekday>(__mLocalTime.tm_wday);
	}

	/**
		@brief 서버의 시작시간을 받는 함수
		@return const CTime& 서버의 시작시간
	*/
	inline const CTime& CTime::GetStartTime()
	{
		return __mStartTime;
	}

	/**
		@brief TimePoint를 이용하여 현재 설정된 시간으로 업데이트하는 함수
	*/
	inline void CTime::UpdateFromTimePoint()
	{
		using namespace std::chrono;
		time_t aTime = std::move(system_clock::to_time_t(__mTimePoint));

		::LOCALTIME(&__mLocalTime, &aTime);
		__mLocalTime.tm_year += 1900;
	}

	/**
		@brief LocalTime을 이용하여 현재 설정된 시간으로 업데이트하는 함수
	*/
	inline void CTime::UpdateFromLocalTime()
	{
		using namespace std::chrono;
		__mLocalTime.tm_year -= 1900;
		time_t time = std::move(::mktime(&__mLocalTime));
		
		__mLocalTime.tm_year += 1900;
		__mTimePoint = system_clock::from_time_t(time);
	}
}