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
		@brief 시간을 현재 시간으로 설정하는 함수
	*/
	inline CTime::TimePoint CTime::GetTimePoint() const
	{
		return __mTimePoint;
	}

	/**
		@brief			서버의 시간 틱을 구하는 함수
		@details		서버의 틱은 서버 시작시간을 기준으로 경과한 시간을 ms단위로 반환한다.
		@return	Tick	서버의 시간 틱(ms)
	*/
	inline Tick CTime::GetTick() const
	{
		auto startCount = GetStartTime().GetTimePoint();
		auto nowCount	= (__mTimePoint - startCount).count();
		return Tick(nowCount);
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
		time_t time = std::move(system_clock::to_time_t(__mTimePoint));

		::LOCALTIME(&__mLocalTime, &time);
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