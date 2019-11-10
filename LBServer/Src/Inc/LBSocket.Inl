namespace LBNet
{
#pragma region CTcpSocket
	template<typename THandler>
	ErrCode CTcpSocket::ConnectAsync(const char* pIp, unsigned short pPort, THandler&& pHandler)
	{
		LB_ASSERT(pIp != nullptr,		"Error");

		boost::system::error_code aError;
		auto aAddress = asio::ip::make_address(pIp, aError);
		if (aError.value() != 0)
			return aError.value();

		EndPointType aEndPoint(aAddress, pPort);
		_mSocket.open(aEndPoint.protocol(), aError);
		if (aError.value() != 0)
			return aError.value();
		
		_mSocket.async_connect(aEndPoint, CIOContext::Instance().BindExecuter(pHandler));
		return 0;
	}

	template<typename THandler>
	void CTcpSocket::ReceiveAsync(void* pBuffer, int pSize, THandler&& pHandler)
	{
		LB_ASSERT(_mSocket.is_open(), "Error");
		LB_ASSERT(pBuffer != nullptr, "Error");
		LB_ASSERT(pSize > 0, "Error");

		_mSocket.async_read_some(asio::mutable_buffer(pBuffer, pSize), CIOContext::Instance().BindExecuter(pHandler));
	}

	template<typename THandler>
	void CTcpSocket::SendAsync(void* pBuffer, int pSize, THandler&& pHandler)
	{
		LB_ASSERT(_mSocket.is_open(), "Error");
		LB_ASSERT(pBuffer != nullptr, "Error");
		LB_ASSERT(pSize > 0, "Error");

		_mSocket.async_write_some(asio::mutable_buffer(pBuffer, pSize), CIOContext::Instance().BindExecuter(pHandler));
	}
#pragma endregion CTcpSocket

#pragma region CUdpSocket
	template<typename THandler>
	void CUdpSocket::ReceiveFromAsync(void* pBuffer, int pSize, EndPointType& pEndPoint, THandler&& pHandler)
	{
		LB_ASSERT(__mSocket.is_open(), "Error");
		LB_ASSERT(pBuffer != nullptr, "Error");
		LB_ASSERT(pSize > 0, "Error");

		__mSocket.async_receive_from(asio::mutable_buffer(pBuffer, pSize), pEndPoint, CIOContext::Instance().BindExecuter(pHandler));
	}

	template<typename THandler>
	void CUdpSocket::SendToAsync(void* pBuffer, int pSize, EndPointType& pEndPoint, THandler&& pHandler)
	{
		LB_ASSERT(__mSocket.is_open(), "Error");
		LB_ASSERT(pBuffer != nullptr, "Error");
		LB_ASSERT(pSize > 0, "Error");

		__mSocket.async_send_to(asio::mutable_buffer(pBuffer, pSize), pEndPoint, CIOContext::Instance().BindExecuter(pHandler));
	}
#pragma endregion CUdpSocket
}