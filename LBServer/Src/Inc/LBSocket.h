/**
	@file	LBSocket.h
	@brief	LBServer의 네트워크 소켓 관련 헤더
	@date	2019-08-15
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBServer.h"
#include "LBIOContext.h"

namespace LBNet
{
	/**
		@brief		TCP 소켓 클래스
		@warnning	accept는 acceptor을 이용한다.
		@date		2019-08-15
		@auther		light8reeze(light8reeze@gmail.com)
	*/
	class LBS_EXPORT CTcpSocket
	{
	public:
		using SocketType	= boost::asio::ip::tcp::socket;
		using EndPointType	= boost::asio::ip::tcp::endpoint;

	public:
		CTcpSocket();
		~CTcpSocket();
		
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

		void SetReuse(bool pIsReuse);

		const SocketType&		GetSocket() const;
		SocketType&				GetSocket();
		const EndPointType&&	GetEndPoint() const;

	private:
		SocketType		_mSocket;
	};

	/**
		@brief		UDP 소켓 클래스
		@date		2019-11-10
		@auther		light8reeze(light8reeze@gmail.com)
	*/
	class LBS_EXPORT CUdpSocket
	{
	public:
		using SocketType	= boost::asio::ip::udp::socket;
		using EndPointType	= boost::asio::ip::udp::endpoint;

	public:
		CUdpSocket();
		~CUdpSocket();

		ErrCode ReceiveFrom(void* pBuffer, int pSize, int& pReceivedSize, EndPointType& pEndPoint);
		ErrCode SendTo(void* pBuffer, int pSize, int& pSendSize, EndPointType& pEndPoint);
		ErrCode Close();

		template<typename THandler>
		void ReceiveFromAsync(void* pBuffer, int pSize, EndPointType& pEndPoint, THandler&& pHandler);
		template<typename THandler>
		void SendToAsync(void* pBuffer, int pSize, EndPointType& pEndPoint, THandler&& pHandler);

		void SetReuse(bool pIsReuse);

		const SocketType&		GetSocket() const;
		SocketType&				GetSocket();
		const EndPointType&&	GetEndPoint() const;

	private:
		SocketType		__mSocket;
	};
}

#include "LBSocket.Inl"