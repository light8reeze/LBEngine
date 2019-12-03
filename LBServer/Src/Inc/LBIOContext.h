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
		CIOContext();
		~CIOContext();

		ErrCode Run();
		void	Stop();
		void	Restart();

		template<typename THandler>
		auto BindExecuter(THandler&& pHandler);
		template<typename THandler>
		void Post(THandler&& pHandler);

		asio::io_context&	GetIOContext();
		static CIOContext&	Instance();

	private:
		static CIOContext			__mSingleton;

		#pragma warning(disable : 4251)
		asio::io_context			__mIOContext;
		asio::io_context::strand	__mStrand;
		asio::io_context::work		__mWork;
		#pragma warning(default : 4251)
	};
}

#include "LBIOContext.Inl"