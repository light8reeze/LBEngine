/**
	@file	LBUdpHandler.h
	@brief	LBServer의 UDP 네트워크 이벤트 처리 관련 헤더
	@date	2020-04-06
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBHandler.h"

namespace LBNet
{
	class CUdpObject;

	/**
		@brief		UDP 패킷 이벤트 타입 정의
	*/
	using UDPHandleType = std::function<ErrCode(CPacketHeader*, Size, CUdpObject&)>;
	
	#pragma warning(disable : 4251)
	class LBS_EXPORT CUdpHandler : public CMessageHandler<UDPHandleType>
	{
	private:
		CUdpHandler() = default;

		static CUdpHandler __mSingleton;

	public:
		static CUdpHandler& Instance();
	};
	#pragma warning(default : 4251)
}