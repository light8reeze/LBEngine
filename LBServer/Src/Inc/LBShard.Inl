namespace LBNet
{
	template<typename TShardObject>
	inline CShard<TShardObject>::CShard() : CSession(), __mServerNo(0),
		__mIp(), __mPort(0), __mNextConnect(true)
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
		_mSocket.ConnectAsync(__mIp.c_str(), __mPort,
			[this](const boost::system::error_code& pError)
		{
			auto aShardObject = GetGameObject<TShardObject>();
			if (pError.value() != 0)
			{
				__OnConnectFail(pError.value());
				return;
			}

			ErrCode aErr = OnAccept();
			if (aErr != 0)
			{
				__OnConnectFail(aErr);
			}

			_mLastError = 0;
			aErr = aShardObject->OnConnect();
			if (aErr != 0)
			{
				__OnConnectFail(aErr);
				return;
			}
		});

		return 0;
	}

	template<typename TShardObject>
	ErrCode CShard<TShardObject>::SetDisconnect(ErrCode pError)
	{
		LB_ASSERT(_mLastError == 0, "Invalid!");

		WriteLock aLock(*this);

		if (_mState != EState::eDisconnect)
		{
			_mSocket.Close();
			_mState = EState::eDisconnect;
			_mLastError = pError;

			LB_ASSERT(GetGameObject() != nullptr, "Error!");
			GetGameObject()->OnDisconnect();
		}

		return 0;
	}

	template<typename TShardObject>
	void CShard<TShardObject>::__OnConnectFail(ErrCode pErr)
	{
		auto aShardObject = GetGameObject<TShardObject>();

		WriteLock aLock(*this);

		__mNextConnect = aShardObject->OnConnectFail(pErr);

		if (__mNextConnect)
			Connect();
		else
			SetDisconnect();
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
}