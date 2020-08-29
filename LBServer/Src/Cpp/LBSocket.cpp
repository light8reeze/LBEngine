#include "LBSocket.h"
#include "LBIOContext.h"

namespace LBNet
{
#pragma region CTcpSocket
	CTcpSocket::CTcpSocket() : _mSocket(CIOContext::Instance().GetIOContext())
	{
	}

	CTcpSocket::~CTcpSocket()
	{
		Close();
	}

	ErrCode CTcpSocket::Connect(const char* pIp, unsigned short pPort)
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

	ErrCode CTcpSocket::Receive(void* pBuffer, int pSize, int& pReceivedSize)
	{
		LB_ASSERT(_mSocket.is_open(),	"Error");
		LB_ASSERT(pBuffer != nullptr,	"Error");
		LB_ASSERT(pSize > 0,			"Error");

		boost::system::error_code aError;
		std::size_t aSize = _mSocket.read_some(asio::mutable_buffer(pBuffer, pSize), aError);
		pReceivedSize = static_cast<int>(aSize);
		return aError.value();
	}

	ErrCode CTcpSocket::Send(void* pBuffer, int pSize, int& pSendSize)
	{
		LB_ASSERT(_mSocket.is_open(),	"Error");
		LB_ASSERT(pBuffer != nullptr,	"Error");
		LB_ASSERT(pSize > 0,			"Error");

		boost::system::error_code aError;
		std::size_t aSize = _mSocket.write_some(asio::mutable_buffer(pBuffer, pSize), aError);
		pSendSize = static_cast<int>(aSize);
		return aError.value();
	}

	void CTcpSocket::SetReuse(bool pIsReuse)
	{
		boost::asio::socket_base::reuse_address aOption(pIsReuse);
		_mSocket.set_option(aOption);
	}

	ErrCode CTcpSocket::Close()
	{
		boost::system::error_code aError;

		if(_mSocket.is_open())
			_mSocket.close(aError);
		
		return aError.value();
	}

	const CTcpSocket::SocketType& CTcpSocket::GetSocket() const
	{
		return _mSocket;
	}

	CTcpSocket::SocketType& CTcpSocket::GetSocket()
	{
		return _mSocket;
	}

	const CTcpSocket::EndPointType CTcpSocket::GetEndPoint() const
	{
		return _mSocket.local_endpoint();
	}
#pragma endregion CTcpSocket

#pragma region CUdpSocket
	CUdpSocket::CUdpSocket() : __mSocket(CIOContext::Instance().GetIOContext(), EndPointType())
	{
	}

	CUdpSocket::~CUdpSocket()
	{
		Close();
	}

	ErrCode CUdpSocket::ReceiveFrom(void* pBuffer, int pSize, int& pReceivedSize, EndPointType& pEndPoint)
	{
		LB_ASSERT(__mSocket.is_open(), "Error");
		LB_ASSERT(pBuffer != nullptr, "Error");
		LB_ASSERT(pSize > 0, "Error");

		boost::system::error_code aError;
		std::size_t aSize = __mSocket.receive_from(asio::mutable_buffer(pBuffer, pSize), pEndPoint, 0, aError);
		pReceivedSize = static_cast<int>(aSize);
		return aError.value();
	}

	ErrCode CUdpSocket::SendTo(void* pBuffer, int pSize, int& pSendSize, EndPointType& pEndPoint)
	{
		LB_ASSERT(__mSocket.is_open(), "Error");
		LB_ASSERT(pBuffer != nullptr, "Error");
		LB_ASSERT(pSize > 0, "Error");

		boost::system::error_code aError;
		std::size_t aSize = __mSocket.send_to(asio::mutable_buffer(pBuffer, pSize), pEndPoint, 0, aError);
		pSendSize = static_cast<int>(aSize);
		return aError.value();
	}

	void CUdpSocket::SetReuse(bool pIsReuse)
	{
		boost::asio::socket_base::reuse_address aOption(pIsReuse);
		__mSocket.set_option(aOption);
	}

	ErrCode CUdpSocket::Close()
	{
		boost::system::error_code aError;

		if (__mSocket.is_open())
			__mSocket.close(aError);

		return aError.value();
	}

	const CUdpSocket::SocketType& CUdpSocket::GetSocket() const
	{
		return __mSocket;
	}

	CUdpSocket::SocketType& CUdpSocket::GetSocket()
	{
		return __mSocket;
	}

	const CUdpSocket::EndPointType&& CUdpSocket::GetEndPoint() const
	{
		return std::move(__mSocket.local_endpoint());
	}
#pragma endregion CTcpSocket
}