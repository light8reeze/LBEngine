/**
	@file	LBServer.h
	@brief	LBServer common header file
	@date	2019-07-29
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once

/**
	@brief		boost library config macro
	@comment	Define USE_CUSTOM_LB_BOOST_CONFIG before including to use custom boost config.
*/
#ifndef USE_CUSTOM_LB_BOOST_CONFIG
#include "LBBoostConfig.h"
#endif //USE_CUSTOM_LB_BOOST_CONFIG

/**
	@brief		LBUtility module include
	@warning	Include after asio because LBUtility includes Windows.h
*/
#define LOAD_LBUTILL
#include "LBUtility.h"

#include "boost/asio.hpp"

/**
	@brief		DllExport macro
	@details	Define LOAD_LBSERVER before including LBServer.h when building application with dll.
*/
#ifdef DEVELOP_MODE
	#define LBS_EXPORT
	#define LBS_EXPORT_TEMPLATE
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
	@brief		LBUtility library link
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
		@brief			Get LBServer version
		@return Version	LBServer version
	*/
	constexpr Version LBS_EXPORT GetLBSVersion();

#pragma region Constant
	constexpr Size eSzPacketMax		= 0x3FFF;	// Max packet size
	constexpr auto eTimeRetryAccept = 1s;		// Accept retry time
	constexpr Size eSzSendChunk		= 1 << 10;	// Send buffer size (1KB)
	constexpr Size eSzTimerTask		= 2000;		// Timer task default count
	constexpr Size eSzLogCnt		= 200;		// Log buffer default count
#pragma endregion

	template <typename TObject>
	using SharedObject	= std::shared_ptr<TObject>;
	template <typename TObject>
	using WeakObject	= std::weak_ptr<TObject>;
	template <typename TObject>
	using UniqueObject	= std::unique_ptr<TObject>;

	/**
		@brief			Check if weak_ptr is initialized
		@return bool	Initialization status
	*/
	template <typename T>
	inline bool IsWeakInitialized(std::weak_ptr<T> const& weak)
	{
		using wt = std::weak_ptr<T>;
		auto aWt = wt{};
		return (weak.owner_before(aWt) || aWt.owner_before(weak));
	}

	/**
		@brief				Cast shared_ptr and return as weak_ptr
		@return weak_ptr	Result weak_ptr
	*/
	template <typename TBase, typename TDrived>
	inline WeakObject<TDrived> CastToWeak(SharedObject<TBase>& pShared)
	{
		return WeakObject<TDrived>(std::dynamic_pointer_cast<TDrived>(pShared));
	}

	/**
		@brief				Cast shared_ptr
		@return shared_ptr	Result shared_ptr
	*/
	template <typename TBase, typename TDrived>
	inline SharedObject<TDrived> SharedCast(SharedObject<TBase>& pShared)
	{
		return std::dynamic_pointer_cast<TDrived>(pShared);
	}
}

#include "LBError.h"
