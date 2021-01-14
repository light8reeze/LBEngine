namespace LBNet
{
	/**
		@brief		CTime의 +=연산자
	*/
	template<class Rep, class Period>
	inline CTime& CTime::operator+=(const std::chrono::duration<Rep, Period>& pTime)
	{
		__mTimePoint += pTime;
		__UpdateFromTimePoint();

		return (*this);
	}

	/**
		@brief		CTime의 -=연산자
	*/
	template<class Rep, class Period>
	inline CTime& CTime::operator-=(const std::chrono::duration<Rep, Period>& pTime)
	{
		__mTimePoint -= pTime;
		__UpdateFromTimePoint();

		return (*this);
	}

	/**
		@brief		CTime의 +연산자
	*/
	template< class Rep, class Period>
	inline CTime CTime::operator+(const std::chrono::duration<Rep, Period>& pTime)
	{
		CTime aTime;
		TimePoint point = __mTimePoint + pTime;
		aTime.SetTimePoint(std::move(point));

		return aTime;
	}

	/**
		@brief		CTime의 -연산자
	*/
	template<class Rep, class Period>
	inline CTime CTime::operator-(const std::chrono::duration<Rep, Period>& pTime)
	{
		CTime time;
		TimePoint point = __mTimePoint - pTime;
		time.SetTimePoint(std::move(point));

		return time;
	}
}