/**
	@file	LBSession.h
	@brief	LBUtility�� ��Ʈ��ũ ���� ���� ���
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
		@brief	���� Ŭ����
		@param TProtocol : ����� ������ ��������(boost::asio�� Protocol�� �����ؾ� �Ѵ�.)
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