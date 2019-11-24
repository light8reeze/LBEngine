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
		using HandlerList	= std::map<MessageNumber, HandlerType>;

	public:
		static ErrCode Register(MessageNumber pNumber, THandler&& pHandler);

		template<typename... TArgs>
		static ErrCode Process(MessageNumber pNumber, TArgs... pArgs);

	private:
		static HandlerList	__mHandlerList;
	};
}

#include "LBHandler.Inl"