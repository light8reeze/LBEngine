/**
	@file	LBTcpHandler.h
	@brief	LBServer의 TCP 네트워크 이벤트 처리 관련 헤더
	@date	2020-04-06
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBHandler.h"

namespace LBNet
{
	class CGameObject;

	/**
		@brief		TCP 패킷 이벤트 타입 정의
	*/
	using TCPHandleType = std::function<ErrCode(CPacketHeader*, Size, SharedObject<CGameObject>&)>;
	
	#pragma warning(disable : 4251)
	class LBS_EXPORT CTcpHandler : public CMessageHandler<TCPHandleType>
	{
	private:
		CTcpHandler() = default;

		static CTcpHandler __mSingleton;

	public:
		static CTcpHandler& Instance();
	};
	#pragma warning(default : 4251)
}