/**
	@file	LBSocket.h
	@brief	LBServer�� ��Ʈ��ũ ���� ���� ���
	@date	2019-08-15
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBServer.h"
#include "LBBuffer.h"

namespace LBNet
{
	using namespace boost;

	/**
		@brief		TCP ���� Ŭ����
		@date		2019-08-15
		@auther		light8reeze(light8reeze@gmail.com)
	*/
	class LBS_EXPORT CTCPSocket
	{
	public:
		using SocketType	= asio::ip::tcp::socket;
		using EndPointType	= asio::ip::tcp::endpoint;
		using PacketBuffer	= CAsyncBuffer<eSzPacketBuffer, eSzPacketMax>;

	public:
		CTCPSocket();
		~CTCPSocket();

		SocketType&		GetSocket();
		EndPointType&	GetEndPoint();

	private:
		SocketType		__mSocket;
		PacketBuffer	__mBuffer;
	};
}