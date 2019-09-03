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

#include "boost/asio.hpp"

/**
	@brief		LBUtility사용 설정
	@warning	LBUtility에 Windows.h가 포함되어있기 때문에 asio보다 아래에 포함한다.
*/
#define LOAD_LBUTILL
#include "LBUtility.h"


/**
	@brief		DllExport 관련 매크로
	@details	dll을 받아 어플리케이션을 구현할 때에는 LBServer.h를 정의하기 전에 LOAD_LBSERVER매크로를 정의한다.
*/
#ifdef DEVELOP_MODE
	#define LBS_EXPORT
#else
	#ifdef LOAD_LBSERVER
		#define LBS_EXPORT	__declspec(dllimport)
	#else
		#define LBS_EXPORT	__declspec(dllexport)
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

	constexpr unsigned int eSzPacketBuffer	= 0xFFFF;	// 패킷 버퍼 최대 사이즈
	constexpr unsigned int eSzPacketMax		= 0x0FFF;	// 한 패킷당 최대 사이즈
	constexpr unsigned int eSzPacketMin		= 4;		// 한 패킷당 최소 사이즈
}