namespace LBNet
{
	template<typename THandler>
	ErrCode CTCPSocket::ConnectAsync(const char* pIp, unsigned short pPort, THandler&& pHandler)
	{
		LB_ASSERT(pIp != nullptr,		"Error");

		boost::system::error_code aError;
		auto aAddress = asio::ip::make_address(pIp, aError);
		if (aError.value() != 0)
			return aError.value();

		EndPointType aEndPoint(aAddress, pPort);
		__mSocket.open(aEndPoint.protocol(), aError);
		if (aError.value() != 0)
			return aError.value();
		
		__mSocket.async_connect(aEndPoint, THandler);
		return 0;
	}

	template<typename THandler>
	void CTCPSocket::ReceiveAsync(void* pBuffer, int pSize, THandler&& pHandler)
	{
		LB_ASSERT(__mSocket.is_open(), "Error");
		LB_ASSERT(pBuffer != nullptr, "Error");
		LB_ASSERT(pSize > 0, "Error");

		__mSocket.async_read_some(asio::mutable_buffer(pBuffer, pSize), pHandler);
		return 0;
	}

	template<typename THandler>
	void CTCPSocket::SendAsync(void* pBuffer, int pSize, THandler&& pHandler)
	{
		LB_ASSERT(__mSocket.is_open(), "Error");
		LB_ASSERT(pBuffer != nullptr, "Error");
		LB_ASSERT(pSize > 0, "Error");

		__mSocket.async_write_some(asio::mutable_buffer(pBuffer, pSize), pHandler);
		return 0;
	}
}