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
	using MessageNo = unsigned long;

	/**
		@brief	��Ŷ ��� Ŭ����
		@date	2019-08-30
		@auther	light8reeze(light8reeze@gmail.com)
	*/
	#pragma pack(push, 1)
	class CPacketHeader
	{
	public:
		MessageNo mMessage;
	};
	#pragma pack(pop)
	
	/**
		@brief	��Ŷ ó�� Ŭ����
		@param THandler	��Ŷ �̹�Ʈó�� �Լ�Ÿ��
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