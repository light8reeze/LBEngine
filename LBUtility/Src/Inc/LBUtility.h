/**
	@file	LBUtility.h
	@brief	LBUtility를 사용하기 위해 필요한 설정 헤더파일
	@date	2019-02-17
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include <assert.h>

//#define DEVELOP_MODE

#ifdef WIN32
	#define X86
#endif //WIN32

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
#ifndef NOMINMAX
	#define NOMINMAX
#endif

#ifdef _WINDOWS
/////////////////////////////////////////////////////////////////////////
// SDKDDKVer.h를 포함하면 최고 수준의 가용성을 가진 Windows 플랫폼이 정의됩니다.
// 이전 Windows 플랫폼에 대해 응용 프로그램을 빌드하려는 경우에는 SDKDDKVer.h를 포함하기 전에
// WinSDKVer.h를 포함하고 _WIN32_WINNT 매크로를 지원하려는 플랫폼으로 설정하십시오.
#include <SDKDDKVer.h>
/////////////////////////////////////////////////////////////////////////
#endif //_WINDOWS

#include <stdexcept>
#include <type_traits>

/**
	@brief std::chrono_literals 사용 정의
*/
#include <chrono>
using namespace std::chrono_literals;

/**
	@brief		DllExport 관련 매크로
	@details	dll을 받아 어플리케이션을 구현할 때에는 LBUtillity.h를 정의하기 전에 LOAD_LBUTILL매크로를 정의한다.
*/
#ifdef LOAD_LBUTILL
	#define LBU_EXPORT						__declspec(dllimport)
	#define LBU_EXPORT_TEMPLATE(pClass)		extern template class LBU_EXPORT pClass
#else
	#define LBU_EXPORT						__declspec(dllexport)
	#define LBU_EXPORT_TEMPLATE(pClass)		template class LBU_EXPORT pClass
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
	#define DEBUG_CODE(pExp)
#endif //_DEBUG

namespace LBNet
{
	/**
		@brief	LBEngine에서 사용하는 크기 타입 정의
	*/
	using Size = unsigned short;

	/**
		@brief	LBEngine에서 사용하는 기본 시간 단위 정의
	*/
	using Tick		= std::chrono::duration<unsigned long long, std::milli>;
	using TickCount	= Tick::rep;

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
		@param T1		비교할 포인터 타입
		@param T2		비교할 포인터 타입
		@warning		혼동을 피하기 위해 두 인자를 모두 포인터타입을 넣어준다.
						1. 포인터, 일반 변수를 섞어사용할 경우 버그가 발생할 가능성이 높다.
						(ex1 : T1 = int*, T2 = void*) => 포인터비교가 맞게 실행됨
						(ex2 : T1 = int*, T2 = char)  => 포인터비교가 맞게 실행되지 않음
						2. const 포인터의 경우 const를 제거하여 인자로 넣어야 한다.
		@return bool	두 포인터가 같은 주소이면 true 아니면 false
	*/
	template<typename T1, typename T2>
	inline bool IsSameAddress(T1 pT1, T2 pT2)
	{
		static_assert(std::is_pointer<T1>::value && std::is_pointer<T2>::value);
		using Non_cvT1 = std::remove_cv_t<T1>;
		using Non_cvT2 = std::remove_cv_t<T2>;

		return (reinterpret_cast<void*>(const_cast<Non_cvT1>(pT1))
			== reinterpret_cast<void*>(const_cast<Non_cvT2>(pT2)));
	}

	/**
		@brief			LBUtillity의 버전을 받는 함수
		@return Version	LBUtillity의 버전
	*/
	using Version = unsigned int;
	constexpr Version LBU_EXPORT GetLBUVersion();
	
	/**
		@brief			특정 포인터를 할당 해제하는 함수
		@param TType	삭제할 포인터 자료형
		@param TType&	삭제할 포인터
		@warning		TType는 반드시 포인터여야 한다.
	*/
	template<typename TType>
	inline void SafeDelete(TType& pObject)
	{
		static_assert(std::is_pointer<TType>::value);

		if (pObject)
		{
			delete pObject;
			pObject = nullptr;
		}
	}
	
	/**
		@brief			특정 포인터를 할당 해제하는 함수(배열)
		@param TType	삭제할 포인터 자료형
		@param TType&	삭제할 포인터
		@warning		TType는 반드시 포인터여야 한다.
	*/
	template<typename TType>
	inline void SafeArrayDelete(TType& pObject)
	{
		static_assert(std::is_pointer<TType>::value);

		if (pObject)
		{
			delete[] pObject;
			pObject = nullptr;
		}
	}
	
	/**
		@brief 에러코드 타입
	*/
	using ErrCode = std::size_t;
}

/**
	@brief		에러코드 등록 매크로
	@comment	pErr에 사용할 변수명을 넣는다.
*/
#define LB_ERRCODE(pErr) const LBNet::ErrCode pErr = std::hash<std::string>{}(#pErr)