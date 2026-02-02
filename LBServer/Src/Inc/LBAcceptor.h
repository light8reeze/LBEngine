/**
	@file	LBAcceptor.h
	@brief	LBServer의 네트워크 Acceptor 관련 모듈
	@date	2019-08-19
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBServer.h"
#include "LBGameObject.h"

namespace LBNet
{
	/**
		@brief		TCP Acceptor 클래스
		@warnning	현재는 IPv4만 지원한다.(v6 지원예정 없음)
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
		#pragma warning(disable : 4251)
		AcceptorType __mAcceptor;
		#pragma warning(default : 4251)
	};
}

#include "LBAcceptor.Inl"
