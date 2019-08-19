/**
	@file	LBIOContext.h
	@brief	LBServer의 IOContext 관련 헤더
	@date	2019-08-15
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBServer.h"

namespace LBNet
{
	using namespace boost;

	/**
		@brief		IOContext 클래스
		@date		2019-08-15
		@auther		light8reeze(light8reeze@gmail.com)
	*/
	class LBS_EXPORT CIOContext
	{
	public:
		CIOContext() = default;
		~CIOContext();

		ErrCode Run();
		void	Stop();
		void	Restart();

		asio::io_context&	GetIOContext();
		static CIOContext&	Instance();

	private:
		static CIOContext	__mSingleton;
		asio::io_context	__mIOContext;
	};
}