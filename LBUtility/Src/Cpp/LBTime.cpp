#include "LBTime.h"

namespace LBNet
{
	const CTime CTime::__mStartTime;

	/**
		@brief		CTime�� ������
		@details	�ð��� ���� �ð����� �����Ѵ�.
	*/
	CTime::CTime() : __mTimePoint(), __mLocalTime()
	{
		SetNow();
	}

	/**
		@brief		CTime�� +=������
	*/
	CTime& CTime::operator+=(const CTime& pTime)
	{
		__mTimePoint += pTime.GetTimePoint().time_since_epoch();
		__UpdateFromTimePoint();

		return (*this);
	}

	/**
		@brief		CTime�� -=������
	*/
	CTime& CTime::operator-=(const CTime& pTime)
	{
		__mTimePoint -= pTime.GetTimePoint().time_since_epoch();
		__UpdateFromTimePoint();

		return (*this);
	}

	/**
		@brief		CTime�� +������
	*/
	CTime CTime::operator+(const CTime& pTime)
	{
		CTime aTime;
		TimePoint point = __mTimePoint + pTime.GetTimePoint().time_since_epoch();
		aTime.SetTimePoint(std::move(point));

		return aTime;
	}

	/**
		@brief		CTime�� -������
	*/
	CTime CTime::operator-(const CTime& pTime)
	{
		CTime time;
		TimePoint point = __mTimePoint - pTime.GetTimePoint().time_since_epoch();
		time.SetTimePoint(std::move(point));

		return time;
	}

	/**
		@brief �ð��� ���� �ð����� �����ϴ� �Լ�
	*/
	void CTime::SetNow()
	{
		using namespace std::chrono;
		__mTimePoint	= system_clock::now();
		time_t time		= std::move(system_clock::to_time_t(__mTimePoint));
		
		::LOCALTIME(&__mLocalTime, &time);
		__mLocalTime.tm_year += 1900;
	}

	/**
		@brief ������ �����ϴ� �Լ�
		@param int pYear ������ ����
	*/
	void CTime::SetYear(int pYear)
	{
		__mLocalTime.tm_year = pYear;
		__UpdateFromLocalTime();
	}

	/**
		@brief ���� �����ϴ� �Լ�
		@param int pMonth ������ ��
	*/
	void CTime::SetMonth(int pMonth)
	{
		LB_ASSERT(pMonth >= 0 && pMonth < 12, "Invalid Value!");

		__mLocalTime.tm_mon = pMonth;
		__UpdateFromLocalTime();
	}

	/**
		@brief ���� �����ϴ� �Լ�
		@param int pDay ������ ��
	*/
	void CTime::SetDay(int pDay)
	{
		LB_ASSERT(pDay >= 0 && pDay <= 31, "Invalid Value!");

		__mLocalTime.tm_mday = pDay;
		__UpdateFromLocalTime();
	}

	/**
		@brief �ð��� �����ϴ� �Լ�
		@param int pHour ������ �ð�
	*/
	void CTime::SetHour(int pHour)
	{
		LB_ASSERT(pHour >= 0 && pHour <= 24, "Invalid Value!");

		__mLocalTime.tm_hour = pHour;
		__UpdateFromLocalTime();
	}

	/**
		@brief ���� �����ϴ� �Լ�
		@param int pMoinute ������ ��
	*/
	void CTime::SetMinute(int pMinute)
	{
		LB_ASSERT(pMinute >= 0 && pMinute <= 60, "Invalid Value!");

		__mLocalTime.tm_min = pMinute;
		__UpdateFromLocalTime();
	}

	/**
		@brief �ʸ� �����ϴ� �Լ�
		@param int pSecond ������ ��
	*/
	void CTime::SetSecond(int pSecond)
	{
		LB_ASSERT(pSecond >= 0 && pSecond <= 60, "Invalid Value!");

		__mLocalTime.tm_sec = pSecond;
		__UpdateFromLocalTime();
	}

	/**
		@brief TimePoint�� �����ϴ� �Լ�
		@param TimePoint pTimePoint ������ TimePoint
	*/
	void CTime::SetTimePoint(TimePoint pTimePoint)
	{
		__mTimePoint = pTimePoint;
		__UpdateFromTimePoint();
	}

	/**
		@brief TimePoint�� ��ȯ�ϴ� �Լ�
	*/
	CTime::TimePoint CTime::GetTimePoint() const
	{
		return __mTimePoint;
	}

	/**
		@brief			������ �ð� ƽ�� ���ϴ� �Լ�
		@details		������ ƽ�� �ð��� ms������ ��ȯ�Ѵ�.
		@return	Tick	������ �ð� ƽduration(ms)
	*/
	Tick CTime::ToTick() const
	{
		return std::chrono::duration_cast<Tick>(__mTimePoint.time_since_epoch());
	}

	/**
		@brief			������ �ð� ƽ�� ���ϴ� �Լ�
		@details		������ ƽ�� ����� �ð��� ms������ ��ȯ�Ѵ�.
		@return	Tick	������ �ð� ƽTickCount(ms)
	*/
	TickCount CTime::ToTickCount() const
	{
		return std::chrono::duration_cast<Tick>(__mTimePoint.time_since_epoch()).count();
	}

	/**
		@brief	������ ��ȯ�� �Լ�
		@return ������
	*/
	int CTime::GetYear() const
	{
		return __mLocalTime.tm_year;
	}

	/**
		@brief ���� ��ȯ�ϴ� �Լ�
		@return ��
	*/
	int CTime::GetMonth() const
	{
		return __mLocalTime.tm_mon;
	}

	/**
		@brief ���� ��ȯ�ϴ� �Լ�
		@return ��
	*/
	int CTime::GetDay() const
	{
		return __mLocalTime.tm_mday;
	}

	/**
		@brief	�ð��� ��ȯ�ϴ� �Լ�
		@return �ð�
	*/
	int CTime::GetHour() const
	{
		return __mLocalTime.tm_hour;
	}

	/**
		@brief	���� ��ȯ�ϴ� �Լ�
		@return ��
	*/
	int CTime::GetMinute() const
	{
		return __mLocalTime.tm_min;
	}

	/**
		@brief	�ʸ� ��ȯ�ϴ� �Լ�
		@return ��
	*/
	int CTime::GetSecond() const
	{
		return __mLocalTime.tm_sec;
	}

	/**
		@brief		������ ��ȯ�ϴ� �Լ�
		@details	������ �Ͽ���(0) ~ �����(6)�̴�
		@return		����
	*/
	EWeekday CTime::GetWeekday() const
	{
		LB_ASSERT(__mLocalTime.tm_wday >= 0 && __mLocalTime.tm_wday < 7, "Invalid Weekday");
		return static_cast<EWeekday>(__mLocalTime.tm_wday);
	}

	/**
		@brief ������ ���۽ð��� �޴� �Լ�
		@return const CTime& ������ ���۽ð�
	*/
	const CTime& CTime::GetStartTime()
	{
		return __mStartTime;
	}

	Tick CTime::GetSteadyTick()
	{
		return std::chrono::time_point_cast<Tick>(std::chrono::steady_clock::now()).time_since_epoch();
	}

	TickCount CTime::GetSteadyTickCount()
	{
		return GetSteadyTick().count();
	}

	Tick CTime::GetSystemTick()
	{
		return std::chrono::time_point_cast<Tick>(std::chrono::system_clock::now()).time_since_epoch();
	}

	TickCount CTime::GetSystemTickCount()
	{
		return GetSystemTick().count();
	}

	/**
		@brief TimePoint�� �̿��Ͽ� ���� ������ �ð����� ������Ʈ�ϴ� �Լ�
	*/
	void CTime::__UpdateFromTimePoint()
	{
		using namespace std::chrono;
		time_t aTime = std::move(system_clock::to_time_t(__mTimePoint));

		::LOCALTIME(&__mLocalTime, &aTime);
		__mLocalTime.tm_year += 1900;
	}

	/**
		@brief LocalTime�� �̿��Ͽ� ���� ������ �ð����� ������Ʈ�ϴ� �Լ�
	*/
	void CTime::__UpdateFromLocalTime()
	{
		using namespace std::chrono;
		__mLocalTime.tm_year -= 1900;
		time_t time = std::move(::mktime(&__mLocalTime));
		
		__mLocalTime.tm_year += 1900;
		__mTimePoint = system_clock::from_time_t(time);
	}
}
