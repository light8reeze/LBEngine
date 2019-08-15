/**
	@file	LBServer.h
	@brief	LBServer�� ����ϱ� ���� �ʿ��� ���� �������
	@date	2019-07-29
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once

/**
	@brief	LBUtility��� ����
*/
#define LOAD_LBUTILL
#include "LBUtility.h"

/**
	@brief		boost ���̺귯�� ���� ���� ��ũ��
	@comment	������ ����Ҷ� boost���̺귯���� ���� �����Ϸ���
				USE_CUSTOM_LB_BOOST_CONFIG ��ũ�θ� ���� �����Ѵ�.
*/
#ifndef USE_CUSTOM_LB_BOOST_CONFIG
#include "LBBoostConfig.h"
#endif //USE_CUSTOM_LB_BOOST_CONFIG

#include "boost/asio.hpp"


/**
	@brief		DllExport ���� ��ũ��
	@details	dll�� �޾� ���ø����̼��� ������ ������ LBServer.h�� �����ϱ� ���� LOAD_LBSERVER��ũ�θ� �����Ѵ�.
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
	@brief		LBUtility ���̺귯�� ��� ����
*/
#ifdef _DEBUG
	#ifdef X64
		#pragma comment (lib, "LBUtilityD_x64.lib")
	#elif WIN32
		#pragma comment (lib, "LBUtilityD_x86.lib")
	#endif
#elif _NDEBUG
	#ifdef X64
		#pragma comment (lib, "LBUtility_x64.lib")
	#elif WIN32
		#pragma comment (lib, "LBUtility_x86.lib")
	#endif
#endif //_DEBUG

namespace LBNet
{
	/**
		@brief			LBServer�� ������ �޴� �Լ�
		@return Version	LBServer�� ����
	*/
	constexpr Version LBS_EXPORT GetLBSVersion();

	constexpr unsigned int eSzPacketBuffer	= 0xFFFF;	// ��Ŷ ���� �ִ� ������
	constexpr unsigned int eSzPacketMax		= 0x0FFF;	// �� ��Ŷ�� �ִ� ������
}