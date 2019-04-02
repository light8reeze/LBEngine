/**
	@file	LBUtility.h
	@brief	LBUtility를 사용하기 위해 필요한 설정 헤더파일
	@date	2019-02-17
	@auther Light8reeze(light8reeze@gmail.com)
*/
#pragma once
//#include <crtdbg.h>
#include <assert.h>

#define DEVELOP_MODE

/**
	@brief		개발할 OS의 매크로, 추후 포팅을 위해 OS에 종속적인 코드는 다음 매크로로 전처리한다.
	@warning	_WINDOWS, _LINUX 둘다 정의시 컴파일 에러가 발생한다
*/
#define _WINDOWS
//#define _LINUX
#if defined (_WINDOWS) && (_LINUX)
	#error define OS _WINDOWS or _LINUX only
#endif //(_WINDOWS) && (_LINUX)

/**
	@brief windows의 min, max를 사용하지 않고 std의 min, max를 사용한다.
*/
#define NOMINMAX

#ifdef _WINDOWS
#include <Windows.h>
//TODO : OS 독립적인 코드구현을 위해 개발단계에선 포함하지 않는다.
#ifndef DEVELOP_MODE
/////////////////////////////////////////////////////////////////////////
// SDKDDKVer.h를 포함하면 최고 수준의 가용성을 가진 Windows 플랫폼이 정의됩니다.
// 이전 Windows 플랫폼에 대해 응용 프로그램을 빌드하려는 경우에는 SDKDDKVer.h를 포함하기 전에
// WinSDKVer.h를 포함하고 _WIN32_WINNT 매크로를 지원하려는 플랫폼으로 설정하십시오.
#include <SDKDDKVer.h>
/////////////////////////////////////////////////////////////////////////
#endif //DEVELOP_MODE
#endif //_WINDOWS

#include <stdexcept>
#include <type_traits>

/**
	@brief		std::rel_ops 사용 정의 <, == 연산자를 정의함으로 >, != 연산자가 자동 정의된다.
	@warning	std클래스에서 정의된 operator와 중복이 되기때문에 삭제(2019-03-27)
*/
#include <utility>
//using namespace std::rel_ops;

/**
	@brief std::chrono_literals 사용 정의
*/
#include <chrono>
using namespace std::chrono_literals;

/**
	@brief		DllExport 관련 매크로
	@details	dll을 받아 어플리케이션을 구현할 때에는 LBUtillity.h를 정의하기 전에 LOAD_LBUTILL매크로를 정의한다.
*/
//개발단계에서는 제외
#ifdef DEVELOP_MODE
	#define LB_UTILL_EXPORT
#else
	#ifdef LOAD_LBUTILL
		#define LB_UTILL_EXPORT	__declspec(dllimport)
	#else
		#define LB_UTILL_EXPORT	__declspec(dllexport)
	#endif //DEVELOP_MODE
#endif //LOAD_LBUTILL

/**
	@brief		assert 관련 매크로
	@param pExp 검증할 표현식
	@param pMsg	assert발생시 출력할 메세지
*/
#define LB_ASSERT(pExp, pMsg) assert((pExp) && (pMsg))

/**
	@brief		디버그 모드에만 넣을 코드 매크로 (Release모드에선 제외)
	@param pExp 디버그에 사용할 코드
*/
#ifdef _DEBUG
	#define DEBUG_CODE(pExp) pExp
#else
	#define ONLY_DEBUG(pExp)
#endif //_DEBUG

namespace LBNet
{
	/**
		@brief	LBNet에서 사용하는 크기 타입 정의
	*/
	using Size = unsigned int;

	/**
		@brief	LBNet에서 사용하는 기본 시간 단위 정의
	*/
	using Tick		= std::chrono::milliseconds;
	using TickLep	= std::chrono::milliseconds::rep;

	/**
		@brief			Enum을 타입의 값으로 변환해주는 함수
		@param TEnum	변환할 Enum값
		@return auto	변환된 Enum값
	*/
	template<typename TEnum>
	constexpr auto UnderLying(TEnum e) -> typename std::underlying_type<TEnum>::type
	{
		return static_cast<typename std::underlying_type<TEnum>::type>(e);
	}

	/**
		@brief			두 포인터가 같은 주소인지 검사하는 함수
		@param T1		비교할 포인터 값
		@param T2		비교할 포인터 값
		@warning		혼동을 피하기 위해 두 인자를 모두 포인터타입을 넣어준다.
						포인터, 일반 변수를 섞어사용할 경우 버그가 발생할 가능성이 높다.
						(ex1 : T1 = int*, T2 = void*) => 포인터비교가 맞게 실행됨
						(ex2 : T1 = int*, T2 = char)  => 포인터비교가 맞게 실행되지 않음
		@return bool	두 포인터가 같은 주소이면 true 아니면 false
	*/
	template<typename T1, typename T2>
	inline bool IsSameAddress(T1 pT1, T2 pT2)
	{
		if(std::is_same<T1, T2>::value)
			return (pT1 == pT2);

		return (pT1 == reinterpret_cast<T1>(pT2));
	}

	/**
		@brief			LBUtillity의 버전을 받는 함수
		@return Version	LBUtillity의 버전
	*/
	using Version = unsigned int;
	constexpr Version LB_UTILL_EXPORT GetLBUVersion();
}