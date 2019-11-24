/**
	@file	LBClientHandler.h
	@brief	LBClient의 클라이언트 패킷처리 관련 헤더파일
	@date	2019-11-24
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBHandler.h"

namespace LBNet
{
	/**
		@brief	클라이언트 패킷 처리 클래스 타입 정의
	*/
	using PacketHandle	= std::function<ErrCode(CPacketHeader*, Size)>;
	using ClientHandler = CMessageHandler<PacketHandle>;
}