/**
	@file	LBServer.h
	@brief	LBServer를 사용하기 위해 필요한 설정 헤더파일
	@date	2019-07-29
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once

/**
	@brief		boost 라이브러리 설정 관련 매크로
	@comment	서버를 사용할때 boost라이브러리를 직접 설정하려면
				USE_CUSTOM_LB_BOOST_CONFIG 매크로를 먼저 정의한다.
*/
#ifndef USE_CUSTOM_LB_BOOST_CONFIG
#include "LBBoostConfig.h"
#endif //USE_CUSTOM_LB_BOOST_CONFIG

/**
	@brief		LBUtility사용 설정
	@warning	LBUtility에 Windows.h가 포함되어있기 때문에 asio보다 먼저 포함한다.
*/
#define LOAD_LBUTILL
#include "LBUtility.h"

#include "boost/asio.hpp"

/**
	@brief		DllExport 관련 매크로
	@details	dll을 받아 어플리케이션을 구현할 때에는 LBServer.h를 정의하기 전에 LOAD_LBSERVER매크로를 정의한다.
*/
#ifdef DEVELOP_MODE
	#define LBS_EXPORT
#else
	#ifdef LOAD_LBSERVER
		#define LBS_EXPORT						__declspec(dllimport)
		#define LBS_EXPORT_TEMPLATE(pClass)		extern template class LBS_EXPORT pClass
	#else
		#define LBS_EXPORT						__declspec(dllexport)
		#define LBS_EXPORT_TEMPLATE(pClass)		template class LBS_EXPORT pClass
	#endif //LOAD_LBSERVER
#endif //DEVELOP_MODE

/**
	@brief		LBUtility 라이브러리 사용 설정
*/
#ifdef _DEBUG
	#ifdef X64
		#pragma comment (lib, "LBUtilityD_x64.lib")
	#elif WIN32
		#pragma comment (lib, "LBUtilityD_x86.lib")
	#endif
#else
	#ifdef X64
		#pragma comment (lib, "LBUtility_x64.lib")
	#elif WIN32
		#pragma comment (lib, "LBUtility_x86.lib")
	#endif
#endif //_DEBUG

namespace LBNet
{
	/**
		@brief			LBServer의 버전을 받는 함수
		@return Version	LBServer의 버전
	*/
	constexpr Version LBS_EXPORT GetLBSVersion();

#pragma region Constant
	constexpr Size eSzPacketMax		= 0x3FFF;	// 한 패킷당 최대 사이즈
	constexpr auto eTimeRetryAccept = 1s;		// Accept실패시 재시도 시간
	constexpr Size eSzSendChunk		= 1 << 10;	// Send블록의 단위(1KB)
	constexpr Size eSzTimerTask		= 2000;		// Timer작업 기본 할당 개수
	constexpr Size eSzLogCnt		= 200;		// 로그버퍼 기본 할당 개수
#pragma endregion

	template <typename TObject>
	using SharedObject	= std::shared_ptr<TObject>;
	template <typename TObject>
	using WeakObject	= std::weak_ptr<TObject>;
	template <typename TObject>
	using UniqueObject	= std::unique_ptr<TObject>;

	/**
		@brief			weak_ptr이 초기화 되어있는지 확인하는 함수
		@return bool	weak_ptr의 초기화 여부
	*/
	template <typename T>
	inline bool IsWeakInitialized(std::weak_ptr<T> const& weak)
	{
		using wt = std::weak_ptr<T>;
		auto aWt = wt{};
		return (weak.owner_before(aWt) || aWt.owner_before(weak));
	}

	/**
		@brief				shared_ptr을 캐스팅 후 weak_ptr을 반환하는 함수.
		@return weak_ptr	반환 결과 weak_ptr
	*/
	template <typename TBase, typename TDrived>
	inline WeakObject<TDrived> CastToWeak(SharedObject<TBase>& pShared)
	{
		SharedObject<TDrived> aDrived = std::dynamic_pointer_cast<TDrived>(pShared);
		return WeakObject<TDrived>(aDrived);
	}

	/**
		@brief				shared_ptr을 캐스팅 후 weak_ptr을 반환하는 함수.
		@return weak_ptr	반환 결과 weak_ptr
	*/
	template <typename TBase, typename TDrived>
	inline SharedObject<TDrived> SharedCast(SharedObject<TBase>& pShared)
	{
		return std::dynamic_pointer_cast<TDrived>(pShared);
	}
}

#include "LBError.h"