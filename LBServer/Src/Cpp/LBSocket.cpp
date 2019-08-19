#include "LBSocket.h"
#include "LBIOContext.h"

namespace LBNet
{
	CTCPSocket::CTCPSocket() : __mSocket(CIOContext::Instance().GetIOContext())
	{
	}

	CTCPSocket::~CTCPSocket()
	{
		Close();
	}

	ErrCode CTCPSocket::Connect(const char* pIp, unsigned short pPort)
	{
		LB_ASSERT(pIp != nullptr, "Error");

		boost::system::error_code aError;
		auto aAddress = asio::ip::make_address(pIp, aError);
		if (aError.value() != 0)
			return aError.value();

		EndPointType aEndPoint(aAddress, pPort);
		__mSocket.open(aEndPoint.protocol(), aError);
		if (aError.value() != 0)
			return aError.value();

		__mSocket.connect(aEndPoint, aError);
		return aError.value();
	}

	ErrCode CTCPSocket::Receive(void* pBuffer, int pSize, int& pReceivedSize)
	{
		LB_ASSERT(__mSocket.is_open(),	"Error");
		LB_ASSERT(pBuffer != nullptr,	"Error");
		LB_ASSERT(pSize > 0,			"Error");

		boost::system::error_code aError;
		std::size_t aSize = __mSocket.read_some(asio::mutable_buffer(pBuffer, pSize), aError);
		pReceivedSize = static_cast<int>(aSize);
		return aError.value();
	}

	ErrCode CTCPSocket::Send(void* pBuffer, int pSize, int& pSendSize)
	{
		LB_ASSERT(__mSocket.is_open(),	"Error");
		LB_ASSERT(pBuffer != nullptr,	"Error");
		LB_ASSERT(pSize > 0,			"Error");

		boost::system::error_code aError;
		std::size_t aSize = __mSocket.write_some(asio::mutable_buffer(pBuffer, pSize), aError);
		pSendSize = static_cast<int>(aSize);
		return aError.value();
	}

	ErrCode CTCPSocket::Close()
	{
		LB_ASSERT(__mSocket.is_open(),	"Error");

		boost::system::error_code aError;
		__mSocket.close(aError);
		return aError.value();
	}

	const CTCPSocket::SocketType& CTCPSocket::GetSocket() const
	{
		return __mSocket;
	}

	CTCPSocket::SocketType& CTCPSocket::GetSocket()
	{
		return __mSocket;
	}

	const CTCPSocket::EndPointType CTCPSocket::GetEndPoint() const
	{
		return __mSocket.local_endpoint();
	}
}