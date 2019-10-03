/**
	@file	LBIOContext.h
	@brief	LBServer�� IOContext ���� ���
	@date	2019-08-15
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBServer.h"

namespace LBNet
{
	using namespace boost;

	/**
		@brief		IOContext Ŭ����
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
		asio::io_context			__mIOContext;
		asio::io_context::strand	__mStrand;
		asio::io_context::work		__mWork;
	};
}

#include "LBIOContext.Inl"