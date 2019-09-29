/**
	@file	LBHandler.h
	@brief	LBServer�� ��Ʈ��ũ �̺�Ʈ ó�� ���� ���
	@date	2019-08-30
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBServer.h"
#include <functional>
#include <map>

namespace LBNet
{
	class CGameObject;

	using MessageNumber = unsigned long;
	/**
		@brief	��Ŷ ��� Ŭ����
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

	using HandlerType = std::function<ErrCode(CPacketHeader*, Size, SharedObject<CGameObject>&)>;
	
	/**
		@brief	��Ŷ ó�� Ŭ����
		@date	2019-08-30
		@auther	light8reeze(light8reeze@gmail.com)
	*/
	class LBS_EXPORT CMessageHandler
	{
	private:
		using __HandlerList = std::map<MessageNumber, HandlerType>;

	public:
		static ErrCode Register(MessageNumber pNumber, HandlerType&& pHandler);
		static ErrCode Process(MessageNumber pNumber, CPacketHeader* pData, Size pDataSize, SharedObject<CGameObject>& pObject);

	private:
		static __HandlerList	__mHandlerList;
	};
}