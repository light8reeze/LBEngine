namespace LBNet
{
	template<typename TShardObject>
	inline CShard<TShardObject>::CShard() : CSession(), __mServerNo(0),
		__mIp(), __mPort(0), __mNextConnect(false)
	{
		static_assert(std::is_base_of<CShardObject, TShardObject>::value == true);
	}

	template<typename TShardObject>
	ErrCode CShard<TShardObject>::Initialize()
	{
		__super::Initialize();

		return Connect();
	}

	template<typename TShardObject>
	ErrCode CShard<TShardObject>::Connect()
	{
		OnConstruct();

		_mSocket.ConnectAsync(__mIp.c_str(), __mPort,
			[this](const boost::system::error_code& pError)
		{
			auto aShardObject = GetGameObject<TShardObject>();
			if (pError.value() != 0)
			{
				__OnConnectFail(pError.value());
				return;
			}


			ErrCode aErr = aShardObject->OnConnect();
			if (aErr != 0)
			{
				__OnConnectFail(aErr);
				return;
			}

			aErr = OnAccept();
			if (aErr != 0)
			{
				__OnConnectFail(aErr);
			}
		});

		return 0;
	}

	template<typename TShardObject>
	ErrCode CShard<TShardObject>::Close()
	{
		LB_ASSERT(GetGameObject() != nullptr, "Invalid!");

		WriteLock aLocker(_mMutex);

		++(_mSessionKey.mField.mReuse);
		GetGameObject()->OnDisconnect();
		if (__mNextConnect)
		{
			Connect();
		}

		return 0;
	}

	template<typename TShardObject>
	void CShard<TShardObject>::__OnConnectFail(ErrCode pErr)
	{
		auto aShardObject = GetGameObject<TShardObject>();

		SetDisconnect();

		WriteLock aLocker(_mMutex);

		__mNextConnect = aShardObject->OnConnectFail(pErr);
	}

	template<typename TShardObject>
	inline void CShard<TShardObject>::SetAddress(const char* pIp, unsigned short pPort)
	{
		LB_ASSERT(pIp != nullptr, "Error!");

		__mIp = pIp;
		__mPort = pPort;
	}

	template<typename TShardObject>
	inline void CShard<TShardObject>::SetServerNo(unsigned short pServerNo)
	{
		__mServerNo = pServerNo;
	}

	template<typename TShardObject>
	inline unsigned short CShard<TShardObject>::GetServerNo() const
	{
		return __mServerNo;
	}

	template<typename TShardObject>
	inline void CShard<TShardObject>::OnDelete()
	{
		CManagedObject::OnDelete();
		Close();
	}
}