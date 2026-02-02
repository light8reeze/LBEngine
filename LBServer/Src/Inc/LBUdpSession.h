#pragma once
#include "LBServer.h"
#include "LBSocket.h"
#include "LBSender.h"
#include "LBUdpHandler.h"

namespace LBNet
{
	class CUdpObject;

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
		
		#pragma warning(disable : 4251)
		CUdpSocket::EndPointType	__mEndPoint;
		#pragma warning(default : 4251)
		CUdpSocket					__mSocket;
		CBuffer						__mBuffer;
	};
}