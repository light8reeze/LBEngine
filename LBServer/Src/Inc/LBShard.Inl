namespace LBNet
{
	template<typename THandler>
	ErrCode CShard::Connect(const char* pIp, unsigned short pPort, THandler&& pHandler)
	{
		static_assert(std::is_function<THandler>::value == true);

		_mSocket.ConnectAsync(pIp, pPort,
			[this](const boost::system::error_code& pError)
		{
			if (pError.value() != 0)
			{
				Close();
			}

			Receive();
		});
	}

	void CShard::SetServerNo(int pServerNo)
	{
		__mServerNo = pServerNo;
	}

	int CShard::GetServerNo() const
	{
		return __mServerNo;
	}
}