/**
	@file	LBAcceptor.h
	@brief	LBServer�� ��Ʈ��ũ Acceptor ���� ���
	@date	2019-08-19
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBServer.h"
#include "LBGameObject.h"

namespace LBNet
{
	/**
		@brief		TCP Acceptor Ŭ����
		@warnning	����� IPv4�� �����Ѵ�.(v6 �������� ����)
		@date		2019-08-19
		@auther		light8reeze(light8reeze@gmail.com)
	*/
	class LBS_EXPORT CAcceptor
	{
	public:
		using AcceptorType = asio::ip::tcp::acceptor;

	public:
		CAcceptor();
		CAcceptor(CAcceptor&& pAcceptor);
		CAcceptor(const CAcceptor&) = delete;
		~CAcceptor();

		CAcceptor& operator=(const CAcceptor&) = delete;

		ErrCode Bind(const char* pIp, unsigned short pPort);
		ErrCode Bind(unsigned short pPort);
		ErrCode Listen(int pBackLog = AcceptorType::max_listen_connections);
		ErrCode Accept(CSession& pSession);
		ErrCode Close();

		template<typename THandler>
		void AcceptAsync(CSession& pSession, THandler&& pHandler);

	private:
		AcceptorType __mAcceptor;
	};
}

#include "LBAcceptor.Inl"