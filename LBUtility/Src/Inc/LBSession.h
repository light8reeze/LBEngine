/**
	@file	LBSession.h
	@brief	LBUtility의 네트워크 세션 관련 헤더
	@date	2019-05-11
	@auther Light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBUtility.h"
#include "LBBuffer.h"
#include <boost/asio/socket_base.hpp>

namespace LBNet
{
	using namespace boost;

	/**
		@brief	세션 클래스
		@param TProtocol : 사용할 세션의 프로토콜(boost::asio의 Protocol을 만족해야 한다.)
		@date	2019-05-11
		@auther Light8reeze(light8reeze@gmail.com)
	*/
	template<typename TProtocol>
	class CSession
	{
	private:
		using Socket = asio::basic_socket<TProtocol>;

	public:
		CSession();
		~CSession();

		CSession(const CSession<TProtocol>& pRvalue) = delete;
		CSession<TProtocol>& operator=(const CSession<TProtocol>& pRvalue) = delete;

		ErrCode Read();
		ErrCode Read_Async();
		ErrCode Write();
		ErrCode Write_Async();

	private:
		Socket			__mSocket;
		CAsyncBuffer	__mReadBuffer;
		CAsyncBuffer	__mWriteBuffer;
	};
}