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
	class CUdpObject;

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

	using TCPHandleType = std::function<ErrCode(CPacketHeader*, Size, SharedObject<CGameObject>&)>;
	using UDPHandleType = std::function<ErrCode(CPacketHeader*, Size, CUdpObject&)>;
	
	/**
		@brief	��Ŷ ó�� Ŭ����
		@date	2019-08-30
		@auther	light8reeze(light8reeze@gmail.com)
	*/
	class LBS_EXPORT CMessageHandler
	{
	private:
		using __TCPHandlerList = std::map<MessageNumber, TCPHandleType>;
		using __UDPHandlerList = std::map<MessageNumber, UDPHandleType>;

	public:
		static ErrCode Register(MessageNumber pNumber, TCPHandleType&& pHandler);
		static ErrCode Register(MessageNumber pNumber, UDPHandleType&& pHandler);

		static ErrCode Process(MessageNumber pNumber, CPacketHeader* pData, Size pDataSize, SharedObject<CGameObject>& pObject);
		static ErrCode Process(MessageNumber pNumber, CPacketHeader* pData, Size pDataSize, CUdpObject& pObject);

	private:
		static __TCPHandlerList	__mHandlerList;
		static __UDPHandlerList	__mUDPHandlerList;
	};
}