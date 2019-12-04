/**
	@file	LBClient.h
	@brief	LBClient�� ����ϱ� ���� �ʿ��� ���� �������
	@date	2019-11-24
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once

#define LOAD_LBSERVER
#include "LBServer.h"

/**
	@brief		DllExport ���� ��ũ��
	@details	dll�� �޾� ���ø����̼��� ������ ������ LBClient.h�� �����ϱ� ���� LOAD_LBCLIENT��ũ�θ� �����Ѵ�.
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
	@brief		LBServer ���̺귯�� ��� ����
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
		@brief			LBClient�� ������ �޴� �Լ�
		@return Version	LBClient�� ����
	*/
	constexpr Version LBC_EXPORT GetLBCVersion();
}