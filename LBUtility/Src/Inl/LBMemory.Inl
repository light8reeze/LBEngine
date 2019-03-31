namespace LBNet
{
	//CBuffer
	template<Size TSize, Size TMaxDataSize = TSize>
	CBuffer<TSize, TMaxDataSize>::CBuffer() : __mUseSize(0), __mReadIndex(-1), __mWriteIndex(0), 
		__mPassIndex(-1), __mBuffer(), __mRestBuffer()
	{
		::memset_s(__mBuffer, TSize, 0, TSize);
		::memset_s(__mRestBuffer, TMaxDataSize + sizeof(CBuffer::CHeader), 0, TMaxDataSize + sizeof(CBuffer::CHeader));
	}

	template<Size TSize, Size TMaxDataSize = TSize>
	template<typename TData>
	bool CBuffer<TSize, TMaxDataSize>::Enqueue(const TData& pData)
	{
		constexpr Size aDataSize = sizeof(CBuffer::CHeader) + sizeof(TData);
		LB_ASSERT(sizeof(TData) >= GetMaxDataSize(), "Data size is too big!!");

		Size aCopyableSize = 0;
		Size aRestSize = 0;

		//lock
		Size aUsableSize = GetUsableSize();

		if (aDataSize > aUsableSize)
			return false;

		int aReadIndex	= __mReadIndex;
		int aWriteIndex = __mWriteIndex;

		__mWriteIndex	= aDataSize;
		__mUseSize		+= aDataSize;

		if (__mWriteIndex > GetBufferSize())
			__mWriteIndex -= GetBufferSize();

		if (sizeof(CBuffer::CHeader) > GetBufferSize() - aWriteIndex)
		{
			__mPassIndex	= aWriteIndex;
			aWriteIndex		= 0;
			aCopyableSize	= aDataSize;
		}
		//unlock

		if (aDataSize > aCopyableSize)
			aRestSize = aDataSize - aCopyableSize;


		aCopyableSize = (aReadIndex > aWriteIndex) ? aReadIndex - aWriteIndex : GetBufferSize() - aWriteIndex;
		LB_ASSERT(aCopyableSize > 0, "Invalid Buffer Size");

		if (sizeof(CBuffer::CHeader) > GetBufferSize() - aWriteIndex)
		{
			__mPassIndex	= aWriteIndex;
			aWriteIndex		= 0;
			aCopyableSize	= aDataSize;
		}
		else if (aDataSize > aCopyableSize)
			aRestSize = aDataSize - aCopyableSize;

		CBuffer::CHeader* aHeader	= reinterpret_cast<CBuffer::CHeader*>(__mBuffer + aWriteIndex);
		aHeader->mDataSize			= sizeof(TData);
		aCopyableSize	-= sizeof(CBuffer::CHeader);
		aWriteIndex		+= sizeof(CBuffer::CHeader);

		if (aWriteIndex == GetBufferSize())
			aWriteIndex = 0;

		LB_ASSERT(aWriteIndex > GetBufferSize(), "Invalid Write Index");
		::memcpy_s(__mBuffer + aWriteIndex, aCopyableSize, reinterpret_cast<const void*>(&pData), sizeof(TData));
		aWriteIndex += aCopyableSize;
		
		if (aRestSize > 0)
		{
			LB_ASSERT(aRestSize + aCopyableSize + sizeof(CBuffer::CHeader) == aDataSize, "Wrong Size!");
			::memcpy_s(__mBuffer, aRestSize, reinterpret_cast<const void*>(&pData) + aCopyableSize, sizeof(aRestSize));
			aWriteIndex = aRestSize;
		}

		CheckBufferValid();
		return true;
	}

	template<Size TSize, Size TMaxDataSize = TSize>
	char* CBuffer<TSize, TMaxDataSize>::Dequeue()
	{
		CBuffer::CHeader* aHeader = nullptr;
		int aReadIndex = 0;

		//lock
		if (GetUsingSize() < sizeof(CBuffer::CHeader))
			return nullptr;

		if (__mReadIndex == -1)
			__mReadIndex = 0;

		aReadIndex = __mReadIndex;

		LB_ASSERT(__mReadIndex + sizeof(CBuffer::CHeader) < GetBufferSize(), "Invalid Buffer!");
		aHeader	= reinterpret_cast<CBuffer::CHeader*>(__mBuffer + aReadIndex);
		
		if (GetUsingSize() < sizeof(CBuffer::CHeader) + aHeader->mDataSize)
			return nullptr;
		
		__mReadIndex	+= aHeader->mDataSize + sizeof(CBuffer::CHeader);

		if (__mReadIndex > GetBufferSize())
			__mReadIndex -= GetBufferSize();

		__mUseSize -= aHeader->mDataSize + sizeof(CBuffer::CHeader);
		//unlock

		int aLastIndex = (__mPassIndex == -1) ? GetBufferSize() - 1 : __mPassIndex;
		
		if (aReadIndex + aHeader->mDataSize + sizeof(CBuffer::CHeader) >= aLastIndex)
		{
			int aMaxIndex = aReadIndex + aHeader->mDataSize + sizeof(CBuffer::CHeader);
			int aCopySize = (aLastIndex - aReadIndex + 1);
			int aRestSize = (aMaxIndex - aLastIndex + 1);
		}

		CheckBufferValid();
		return __mBuffer + __mReadIndex + sizeof(CBuffer::CHeader);
	}

	template<Size TSize, Size TMaxDataSize = TSize>
	Size CBuffer<TSize, TMaxDataSize>::GetUsingSize()
	{
		return __mUseSize;
	}

	template<Size TSize, Size TMaxDataSize = TSize>
	Size CBuffer<TSize, TMaxDataSize>::GetUsableSize()
	{
		return GetBufferSize() - __mUseSize;
	}

	template<Size TSize, Size TMaxDataSize = TSize>
	constexpr Size CBuffer<TSize, TMaxDataSize>::GetBufferSize()
	{
		static_assert(TSize > 0);
		return TSize;
	}

	template<Size TSize, Size TMaxDataSize = TSize>
	constexpr Size CBuffer<TSize, TMaxDataSize>::GetMaxDataSize()
	{
		static_assert(TMaxDataSize > 0);
		return TMaxDataSize;
	}
}