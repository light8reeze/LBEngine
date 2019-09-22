namespace LBNet
{
	/**
		@brief CBuffer의 생성자
	*/
	template<Size TSize>
	CBuffer<TSize>::CBuffer() : _mUseSize(0), _mReadIndex(0), _mWriteIndex(0), _mBuffer()
	{
		::memset(_mBuffer, 0, TSize);
	}

	template<Size TSize>
	void CBuffer<TSize>::Clear()
	{
		_mReadIndex		= 0;
		_mUseSize		= 0;
		_mWriteIndex	= 0;
		::memset(_mBuffer, 0, TSize);
	}

	template<Size TSize>
	bool CBuffer<TSize>::Push(const char* pData, Size pSize)
	{
		LB_ASSERT(pData != nullptr, "Error!");
		LB_ASSERT(pSize > 0,		"Error!");

		Size aDataSize = static_cast<Size>(sizeof(CBufferHeader)) + pSize;
		if (aDataSize > GetUsableSize())
			return false;

		reinterpret_cast<CBufferHeader*>(_mBuffer + _mWriteIndex)->mDataSize = pSize;
		::memcpy_s(_mBuffer + _mWriteIndex + sizeof(CBufferHeader), GetUsableSize() - sizeof(CBufferHeader), pData, pSize);
		_mUseSize		+= pSize + sizeof(CBufferHeader);
		_mWriteIndex	+= static_cast<int>(pSize) + sizeof(CBufferHeader);
		return true;
	}

	template<Size TSize>
	char* CBuffer<TSize>::Front(Size& pSize, ErrCode& pErr)
	{
		if (GetUsingSize() < sizeof(CBufferHeader))
			return nullptr;

		pErr = 0;
		char* aData = _mBuffer + _mReadIndex;
		pSize = reinterpret_cast<CBufferHeader*>(aData)->mDataSize;
		aData += sizeof(CBufferHeader);

		if (pSize > TSize - sizeof(CBufferHeader))
			return nullptr;

		_mReadIndex += pSize + sizeof(CBufferHeader);
		return aData;
	}

	template<Size TSize>
	void CBuffer<TSize>::Pop()
	{
		::memmove_s(_mBuffer, TSize, _mBuffer + _mReadIndex, TSize - _mReadIndex);
		_mWriteIndex	-= _mReadIndex;
		_mUseSize		-= static_cast<Size>(_mReadIndex);
		_mReadIndex		= 0;
	}

	template<Size TSize>
	Size CBuffer<TSize>::GetUsingSize() const
	{
		return _mUseSize;
	}

	template<Size TSize>
	Size CBuffer<TSize>::GetUsableSize() const
	{
		return GetBufferSize() - _mUseSize;
	}

	template<Size TSize>
	constexpr Size CBuffer<TSize>::GetBufferSize() const
	{
		//static_assert(TSize > 0);
		return TSize;
	}

	template<Size TSize>
	bool CBuffer<TSize>::OnPush(Size pSize)
	{
		LB_ASSERT(pSize >= sizeof(CBufferHeader),	"Invalid Enqueue!");
		LB_ASSERT(GetUsableSize() >= pSize,			"Invalid Size!");
		
		_mWriteIndex	+= static_cast<int>(pSize);
		_mUseSize		+= pSize;

		return true;
	}

	template<Size TSize>
	char* CBuffer<TSize>::GetWriteAddress()
	{
		LB_ASSERT(_mWriteIndex < TSize, "Invalid Address!");
		return &(_mBuffer[_mWriteIndex]);
	}
}