namespace LBNet
{
	inline CShard::CShard() : CSession(), __mServerNo(0)
	{
	}

	template<typename THandler>
	ErrCode CShard::Connect(const char* pIp, unsigned short pPort, THandler&& pHandler)
	{
		_mSocket.ConnectAsync(pIp, pPort,
			[this, &pHandler](const boost::system::error_code& pError)
		{
			if (pError.value() != 0)
			{
				Close();
			}

			ErrCode aErr = pHandler();

			if (aErr != 0)
			{
				Close();
			}

			OnAccept();
			Receive();
		});

		return 0;
	}

	inline void CShard::SetServerNo(int pServerNo)
	{
		__mServerNo = pServerNo;
	}

	inline int CShard::GetServerNo() const
	{
		return __mServerNo;
	}
}