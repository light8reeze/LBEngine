/**
	@file	LBHandler.h
	@brief	LBServer의 네트워크 이벤트 처리 관련 헤더
	@date	2019-08-30
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBServer.h"
#include "LBPacketHeader.h"
#include <functional>
#include <map>

namespace LBNet
{	
	/**
		@brief	패킷 처리 클래스
		@param THandler	패킷 이번트처리 함수타입
		@date	2019-08-30
		@auther	light8reeze(light8reeze@gmail.com)
	*/
	template<typename THandler>
	class CMessageHandler
	{
	public:
		using HandlerType	= THandler;
		using HandlerList	= std::map<MessageNo, HandlerType>;

	public:
		CMessageHandler() = default;
		~CMessageHandler() = default;
		ErrCode Register(MessageNo pNumber, THandler&& pHandler);
		template<typename... TArgs>
		ErrCode Process(MessageNo pNumber, TArgs... pArgs);

	private:
		HandlerList	__mHandlerList;
	};
}

#include "LBHandler.Inl"