#pragma once
#include "LBServer.h"
#include "LBSocket.h"
#include "LBManagedObject.h"
#include "LBSender.h"
#include "LBHandler.h"

namespace LBNet
{
	class CUdpObject;

	/**
		@brief		UDP 패킷 이벤트 타입 정의
	*/
	using UDPHandleType = std::function<ErrCode(CPacketHeader*, Size, CUdpObject&)>;
	using UDPHandler	= CMessageHandler<UDPHandleType>;

	/**
		@brief		UDP 세션 클래스
		@date		2019-11-10
		@auther		light8reeze(light8reeze@gmail.com)
	*/
	class LBS_EXPORT CUdpSession
	{
	private:
		CUdpSession();
		CUdpSession(const CUdpSession&) = delete;
		CUdpSession& operator=(const CUdpSession&) = delete;

	public:
		~CUdpSession();

		ErrCode ReceiveFrom();
		ErrCode OnReceiveFrom(Size pSize);
		ErrCode SendTo(void* pBuffer, int pSize, CUdpObject& pObject);
		ErrCode SendTo(SharedObject<CSender> pSender, CUdpObject& pObject);

		static CUdpSession& Instance();

	private:
		static CUdpSession __mSingleton;

		CUdpSocket::EndPointType	__mEndPoint;
		CUdpSocket					__mSocket;
		CBuffer						__mBuffer;
	};
}