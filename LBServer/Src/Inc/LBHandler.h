/**
	@file	LBHandler.h
	@brief	LBServer의 네트워크 이벤트 처리 관련 헤더
	@date	2019-08-30
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBServer.h"
#include "LBSession.h"
#include <functional>
#include <map>

namespace LBNet
{
	using MessageNumber = unsigned long;
	/**
		@brief	패킷 헤더 클래스
		@date	2019-08-30
		@auther	light8reeze(light8reeze@gmail.com)
	*/
	#pragma pack(push, 1)
	class CPacketHeader
	{
	public:
		MessageNumber mCommand;
	};
	#pragma pack(pop)

	using HandlerType = std::function<ErrCode(CPacketHeader*, int, CSession&, SharedObject<CGameObject>&)>;
	
	/**
		@brief	패킷 처리 클래스
		@date	2019-08-30
		@auther	light8reeze(light8reeze@gmail.com)
	*/
	class LBS_EXPORT CMessageHandler
	{
	public:

	private:
		using __HandlerList = std::map<MessageNumber, HandlerType>;

	public:
		CMessageHandler(const CMessageHandler&) = delete;
		CMessageHandler(const CMessageHandler&&) = delete;
		const CMessageHandler& operator=(const CMessageHandler&) = delete;

		static ErrCode Register(MessageNumber pNumber, HandlerType&& pHandler);
		static ErrCode Process(MessageNumber pNumber, CPacketHeader* pData, int pDataSize, CSession& pSession, SharedObject<CGameObject>& pObject);

	private:
		static __HandlerList	__mHandlerList;
	};
}