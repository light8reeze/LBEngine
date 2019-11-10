#include "LBUdpObject.h"

namespace LBNet
{
	CUdpObject::CUdpObject() : __mEndPoint()
	{
	}

	CUdpObject::CUdpObject(std::string&& pIp, unsigned short pPort)
		: __mEndPoint(boost::asio::ip::make_address(pIp), pPort)
	{
	}

	CUdpObject::CUdpObject(CUdpSocket::EndPointType& pEndPoint)
		: __mEndPoint(pEndPoint)
	{
	}

	CUdpObject::~CUdpObject()
	{
	}

	ErrCode CUdpObject::SendTo(void* pBuffer, int pSize)
	{
		return CUdpSession::Instance().SendTo(pBuffer, pSize, *this);
	}

	ErrCode CUdpObject::SendTo(SharedObject<CSender>& pSender)
	{
		return CUdpSession::Instance().SendTo(pSender, *this);
	}

	std::string&& CUdpObject::GetIPAddress() const
	{
		return std::move(__mEndPoint.address().to_string());
	}

	unsigned short CUdpObject::GetPort() const
	{
		return __mEndPoint.port();
	}

	CUdpSocket::EndPointType& CUdpObject::GetEndPoint()
	{
		return __mEndPoint;
	}
}