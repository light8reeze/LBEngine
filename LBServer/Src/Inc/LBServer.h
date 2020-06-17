/**
	@file	LBServer.h
	@brief	LBServer�� ����ϱ� ���� �ʿ��� ���� �������
	@date	2019-07-29
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once

/**
	@brief		boost ���̺귯�� ���� ���� ��ũ��
	@comment	������ ����Ҷ� boost���̺귯���� ���� �����Ϸ���
				USE_CUSTOM_LB_BOOST_CONFIG ��ũ�θ� ���� �����Ѵ�.
*/
#ifndef USE_CUSTOM_LB_BOOST_CONFIG
#include "LBBoostConfig.h"
#endif //USE_CUSTOM_LB_BOOST_CONFIG

/**
	@brief		LBUtility��� ����
	@warning	LBUtility�� Windows.h�� ���ԵǾ��ֱ� ������ asio���� ���� �����Ѵ�.
*/
#define LOAD_LBUTILL
#include "LBUtility.h"

#include "boost/asio.hpp"

/**
	@brief		DllExport ���� ��ũ��
	@details	dll�� �޾� ���ø����̼��� ������ ������ LBServer.h�� �����ϱ� ���� LOAD_LBSERVER��ũ�θ� �����Ѵ�.
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
	@brief		LBUtility ���̺귯�� ��� ����
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
		@brief			LBServer�� ������ �޴� �Լ�
		@return Version	LBServer�� ����
	*/
	constexpr Version LBS_EXPORT GetLBSVersion();

#pragma region Constant
	constexpr Size eSzPacketMax		= 0x3FFF;	// �� ��Ŷ�� �ִ� ������
	constexpr auto eTimeRetryAccept = 1s;		// Accept���н� ��õ� �ð�
	constexpr Size eSzSendChunk		= 1 << 10;	// Send����� ����(1KB)
	constexpr Size eSzTimerTask		= 2000;		// Timer�۾� �⺻ �Ҵ� ����
	constexpr Size eSzLogCnt		= 200;		// �α׹��� �⺻ �Ҵ� ����
#pragma endregion

	template <typename TObject>
	using SharedObject	= std::shared_ptr<TObject>;
	template <typename TObject>
	using WeakObject	= std::weak_ptr<TObject>;
	template <typename TObject>
	using UniqueObject	= std::unique_ptr<TObject>;

	/**
		@brief			weak_ptr�� �ʱ�ȭ �Ǿ��ִ��� Ȯ���ϴ� �Լ�
		@return bool	weak_ptr�� �ʱ�ȭ ����
	*/
	template <typename T>
	inline bool IsWeakInitialized(std::weak_ptr<T> const& weak)
	{
		using wt = std::weak_ptr<T>;
		auto aWt = wt{};
		return (weak.owner_before(aWt) || aWt.owner_before(weak));
	}

	/**
		@brief				shared_ptr�� ĳ���� �� weak_ptr�� ��ȯ�ϴ� �Լ�.
		@return weak_ptr	��ȯ ��� weak_ptr
	*/
	template <typename TBase, typename TDrived>
	inline WeakObject<TDrived> CastToWeak(SharedObject<TBase>& pShared)
	{
		SharedObject<TDrived> aDrived = std::dynamic_pointer_cast<TDrived>(pShared);
		return WeakObject<TDrived>(aDrived);
	}

	/**
		@brief				shared_ptr�� ĳ���� �� weak_ptr�� ��ȯ�ϴ� �Լ�.
		@return weak_ptr	��ȯ ��� weak_ptr
	*/
	template <typename TBase, typename TDrived>
	inline SharedObject<TDrived> SharedCast(SharedObject<TBase>& pShared)
	{
		return std::dynamic_pointer_cast<TDrived>(pShared);
	}
}

#include "LBError.h"