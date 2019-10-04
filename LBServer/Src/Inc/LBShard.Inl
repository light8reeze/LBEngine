namespace LBNet
{
	template<typename TShardObject>
	inline CShard<TShardObject>::CShard() : CSession(), __mServerNo(0)
	{
		static_assert(std::is_base_of<CGameObject, TShardObject>::value == true);
	}

	template<typename TShardObject>
	template<typename THandler>
	ErrCode CShard<TShardObject>::Connect(const char* pIp, unsigned short pPort, THandler&& pHandler)
	{
		_mSocket.ConnectAsync(pIp, pPort,
			[this, pHandler](const boost::system::error_code& pError)
		{
			if (pError.value() != 0)
			{
				SetDisconnect();
				Close();
				return ;
			}

			auto aPtr(std::make_shared<TShardObject>());
			SetObject(aPtr);

			OnConstruct();
			OnAccept();

			ErrCode aErr = pHandler();

			if (aErr != 0)
			{
				SetDisconnect();
				Close();
				return;
			}

			Receive();
		});

		return 0;
	}

	template<typename TShardObject>
	inline void CShard<TShardObject>::SetServerNo(int pServerNo)
	{
		__mServerNo = pServerNo;
	}

	template<typename TShardObject>
	inline int CShard<TShardObject>::GetServerNo() const
	{
		return __mServerNo;
	}
}