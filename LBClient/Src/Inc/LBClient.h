/**
	@file	LBClient.h
	@brief	LBClient를 사용하기 위해 필요한 설정 헤더파일
	@date	2019-11-24
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once

#define LOAD_LBSERVER
#include "LBServer.h"

/**
	@brief		DllExport 관련 매크로
	@details	dll을 받아 어플리케이션을 구현할 때에는 LBClient.h를 정의하기 전에 LOAD_LBCLIENT매크로를 정의한다.
*/
//#define DEVELOP_MODE
#ifdef DEVELOP_MODE
	#define LBC_EXPORT
#else
	#ifdef LOAD_LBCLIENT
		#define LBC_EXPORT						__declspec(dllimport)
		#define LBC_EXPORT_TEMPLATE(pClass)		extern template class LBC_EXPORT pClass
	#else
		#define LBC_EXPORT						__declspec(dllexport)
		#define LBC_EXPORT_TEMPLATE(pClass)		template class LBC_EXPORT pClass
	#endif //LOAD_LBCLIENT
#endif //DEVELOP_MODE

/**
	@brief		LBServer 라이브러리 사용 설정
*/
#ifdef _DEBUG
	#ifdef X64
		#pragma comment (lib, "LBServerD_x64.lib")
	#elif WIN32
		#pragma comment (lib, "LBServerD_x86.lib")
	#endif
#else
	#ifdef X64
		#pragma comment (lib, "LBServer_x64.lib")
	#elif WIN32
		#pragma comment (lib, "LBServer_x86.lib")
	#endif
#endif //_DEBUG

namespace LBNet
{
	/**
		@brief			LBClient의 버전을 받는 함수
		@return Version	LBClient의 버전
	*/
	constexpr Version LBC_EXPORT GetLBCVersion();
}