/**
	@file	LBTime.h
	@brief	LBUtillity�� �ð����� ���
	@date	2019-03-16
	@auther Light8reeze(light8reeze@gmail.com)
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
		@todo		duraction litral�� �̿��� ������ �����Ұ�.
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