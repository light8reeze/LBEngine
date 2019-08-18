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
		@warnning	accept�� acceptor�� �̿��Ѵ�.
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

		ErrCode Connect(const char* pIp, unsigned short pPort);
		ErrCode Receive(void* pBuffer, int pSize, int& pReceivedSize);
		ErrCode Send(void* pBuffer, int pSize, int& pSendSize);
		ErrCode Close();

		template<typename THandler>
		ErrCode ConnectAsync(const char* pIp, unsigned short pPort, THandler&& pHandler);
		template<typename THandler>
		void ReceiveAsync(void* pBuffer, int pSize, THandler&& pHandler);
		template<typename THandler>
		void SendAsync(void* pBuffer, int pSize, THandler&& pHandler);

		const SocketType&		GetSocket() const;
		const EndPointType&		GetEndPoint() const;

	private:
		SocketType		__mSocket;
	};
}

#include "LBSocket.Inl"