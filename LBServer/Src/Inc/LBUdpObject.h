#pragma once
#include "LBServer.h"
#include "LBUdpSession.h"

namespace LBNet
{
	/**
		@brief		UDP세션에서 사용하는 오브젝트 클래스
		@date		2019-11-10
		@auther		light8reeze(light8reeze@gmail.com)
	*/
	class LBS_EXPORT CUdpObject
	{
	public:
		CUdpObject();
		CUdpObject(std::string&& pIp, unsigned short pPort);
		CUdpObject(CUdpSocket::EndPointType& pEndPoint);
		~CUdpObject();

	public:
		ErrCode SendTo(void* pBuffer, int pSize);
		ErrCode SendTo(SharedObject<CSender>& pSender);

		std::string&&	GetIPAddress() const;
		unsigned short	GetPort() const;
		CUdpSocket::EndPointType& GetEndPoint();

	private:
		#pragma warning(disable : 4251)
		CUdpSocket::EndPointType __mEndPoint;
		#pragma warning(default : 4251)
	};
}