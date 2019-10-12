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
		if (GetState() == CManagedObject::EState::eReturned)
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
	ErrCode CShard<TShardObject>::SetDisconnect()
	{
		WriteLock aLock(_mMutex);

		if (_mState != EState::eDisconnect)
		{
			_mSocket.Close();
			_mState = EState::eDisconnect;

			LB_ASSERT(GetGameObject() != nullptr, "Error!");
			GetGameObject()->OnDisconnect();
		}

		SetReturn();
		return 0;
	}

	template<typename TShardObject>
	void CShard<TShardObject>::__OnConnectFail(ErrCode pErr)
	{
		auto aShardObject = GetGameObject<TShardObject>();

		WriteLock aLocker(_mMutex);

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

	template<typename TShardObject>
	inline void CShard<TShardObject>::OnDelete()
	{
		CManagedObject::OnDelete();
		Close();
	}
}