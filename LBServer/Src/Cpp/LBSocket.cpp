#include "LBSocket.h"
#include "LBIOContext.h"

namespace LBNet
{
	CTCPSocket::CTCPSocket() : _mSocket(CIOContext::Instance().GetIOContext())
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
		_mSocket.open(aEndPoint.protocol(), aError);
		if (aError.value() != 0)
			return aError.value();

		_mSocket.connect(aEndPoint, aError);
		return aError.value();
	}

	ErrCode CTCPSocket::Receive(void* pBuffer, int pSize, int& pReceivedSize)
	{
		LB_ASSERT(_mSocket.is_open(),	"Error");
		LB_ASSERT(pBuffer != nullptr,	"Error");
		LB_ASSERT(pSize > 0,			"Error");

		boost::system::error_code aError;
		std::size_t aSize = _mSocket.read_some(asio::mutable_buffer(pBuffer, pSize), aError);
		pReceivedSize = static_cast<int>(aSize);
		return aError.value();
	}

	ErrCode CTCPSocket::Send(void* pBuffer, int pSize, int& pSendSize)
	{
		LB_ASSERT(_mSocket.is_open(),	"Error");
		LB_ASSERT(pBuffer != nullptr,	"Error");
		LB_ASSERT(pSize > 0,			"Error");

		boost::system::error_code aError;
		std::size_t aSize = _mSocket.write_some(asio::mutable_buffer(pBuffer, pSize), aError);
		pSendSize = static_cast<int>(aSize);
		return aError.value();
	}

	ErrCode CTCPSocket::Close()
	{
		boost::system::error_code aError;

		if(_mSocket.is_open())
			_mSocket.close(aError);
		
		return aError.value();
	}

	const CTCPSocket::SocketType& CTCPSocket::GetSocket() const
	{
		return _mSocket;
	}

	CTCPSocket::SocketType& CTCPSocket::GetSocket()
	{
		return _mSocket;
	}

	const CTCPSocket::EndPointType CTCPSocket::GetEndPoint() const
	{
		return _mSocket.local_endpoint();
	}
}