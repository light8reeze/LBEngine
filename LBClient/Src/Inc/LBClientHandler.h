/**
	@file	LBClientHandler.h
	@brief	LBClient�� Ŭ���̾�Ʈ ��Ŷó�� ���� �������
	@date	2019-11-24
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBHandler.h"

namespace LBNet
{
	/**
		@brief	Ŭ���̾�Ʈ ��Ŷ ó�� Ŭ���� Ÿ�� ����
	*/
	using PacketHandle	= std::function<ErrCode(CPacketHeader*, Size)>;
	using ClientHandler = CMessageHandler<PacketHandle>;
}