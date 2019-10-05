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
		_mSocket.open(aEndPoint.protocol(), aError);
		if (aError.value() != 0)
			return aError.value();
		
		_mSocket.async_connect(aEndPoint, CIOContext::Instance().BindExecuter(pHandler));
		return 0;
	}

	template<typename THandler>
	void CTCPSocket::ReceiveAsync(void* pBuffer, int pSize, THandler&& pHandler)
	{
		LB_ASSERT(_mSocket.is_open(), "Error");
		LB_ASSERT(pBuffer != nullptr, "Error");
		LB_ASSERT(pSize > 0, "Error");

		_mSocket.async_read_some(asio::mutable_buffer(pBuffer, pSize), CIOContext::Instance().BindExecuter(pHandler));
	}

	template<typename THandler>
	void CTCPSocket::SendAsync(void* pBuffer, int pSize, THandler&& pHandler)
	{
		LB_ASSERT(_mSocket.is_open(), "Error");
		LB_ASSERT(pBuffer != nullptr, "Error");
		LB_ASSERT(pSize > 0, "Error");

		_mSocket.async_write_some(asio::mutable_buffer(pBuffer, pSize), CIOContext::Instance().BindExecuter(pHandler));
	}
}