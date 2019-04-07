namespace LBNet
{
	//CBuffer
	template<Size TSize, Size TMaxDataSize>
	CBuffer<TSize, TMaxDataSize>::CBuffer() : __mUseSize(0), __mReadIndex(-1), __mWriteIndex(0), 
		__mPassIndex(-1), __mBuffer(), __mRestBuffer()
	{
		#pragma warning(disable : 4312)
		DEBUG_CODE(__mCheckCode = reinterpret_cast<char*>(0xDEADBEEFDEADBEEF));
		DEBUG_CODE(__mCheckCode2 = reinterpret_cast<char*>(0xDEADBEEFDEADBEEF));
		#pragma warning(default : 4312)
	}

	template<Size TSize, Size TMaxDataSize>
	template<typename TData>
	bool CBuffer<TSize, TMaxDataSize>::Enqueue(const TData& pData)
	{
		return Enqueue(reinterpret_cast<const char*>(&pData), sizeof(TData));
	}

	template<Size TSize, Size TMaxDataSize>
	bool CBuffer<TSize, TMaxDataSize>::Enqueue(const char* pData, int pSize)
	{
		Size aDataSize = sizeof(CBufferHeader) + pSize;
		LB_ASSERT(pSize <= GetMaxDataSize(), "Data size is too big!!");

		Size aCopyableSize = 0;
		Size aRestSize = 0;

		int aReadIndex = __mReadIndex;
		int aWriteIndex = __mWriteIndex;

		Size aUsableSize = GetUsableSize();

		if (aDataSize > aUsableSize)
			return false;

		aCopyableSize = (aReadIndex > aWriteIndex) ? aReadIndex - aWriteIndex : GetBufferSize() - aWriteIndex;

		if (sizeof(CBufferHeader) > GetBufferSize() - aWriteIndex)
		{
			__mPassIndex = aWriteIndex;
			aWriteIndex = 0;
			aCopyableSize = aDataSize;
		}
		else if (aDataSize > aCopyableSize)
			aRestSize = aDataSize - aCopyableSize;
		else
			aCopyableSize = aDataSize;

		CBufferHeader* aHeader = reinterpret_cast<CBufferHeader*>(__mBuffer + aWriteIndex);
		aHeader->mDataSize = pSize;

		aCopyableSize	-= sizeof(CBufferHeader);
		aWriteIndex		+= sizeof(CBufferHeader);

		if (aWriteIndex == static_cast<int>(GetBufferSize()))
			aWriteIndex = 0;

		LB_ASSERT(aWriteIndex <= static_cast<int>(GetBufferSize()), "Invalid Write Index");
		::memcpy_s(__mBuffer + aWriteIndex, aCopyableSize, pData, aCopyableSize);
		aWriteIndex += aCopyableSize;

		if (aRestSize > 0)
		{
			LB_ASSERT(aRestSize + aCopyableSize + sizeof(CBufferHeader) == aDataSize, "Wrong Size!");
			::memcpy_s(__mBuffer, GetUsableSize() - aCopyableSize, pData + aCopyableSize, aRestSize);
			aWriteIndex = aRestSize;
		}

		LB_ASSERT(aWriteIndex <= static_cast<int>(GetBufferSize()), "Wrong Index");
		if (aWriteIndex == static_cast<int>(GetBufferSize()))
			aWriteIndex = 0;

		{
			std::unique_lock<CLocker> aLocker(__mLocker);

			__mWriteIndex	= aWriteIndex;
			__mUseSize		+= aDataSize;

			if (__mReadIndex == -1)
				__mReadIndex = 0;

			std::cout << "Write : " << __mWriteIndex << " Size : " << aDataSize << std::endl;
		}

		CheckBufferValid();
		return true;
	}

	template<Size TSize, Size TMaxDataSize>
	char* CBuffer<TSize, TMaxDataSize>::Dequeue()
	{
		CBufferHeader* aHeader = nullptr;
		int aReadIndex	= 0;
		int aWriteIndex = 0;
		int aPassIndex	= 0;
		
		if (GetUsingSize() < sizeof(CBufferHeader) || __mReadIndex == -1)
			return nullptr;

		LB_ASSERT(__mReadIndex != -1, "Wrong Index!");
		aReadIndex	= __mReadIndex;
		aWriteIndex = __mWriteIndex;
		aPassIndex	= __mPassIndex.load();
		int aLastIndex = (aPassIndex == -1) ? GetBufferSize() - 1 : aPassIndex - 1;

		if (aReadIndex >= aLastIndex)
		{
			aReadIndex = 0;

			if (aPassIndex != -1)
				__mPassIndex = aPassIndex = -1;
		}

		LB_ASSERT(aReadIndex + sizeof(CBufferHeader) <= aLastIndex + 1, "Invalid Buffer!");
		aHeader		= reinterpret_cast<CBufferHeader*>(__mBuffer + aReadIndex);
		aReadIndex += sizeof(CBufferHeader);
		
		LB_ASSERT(aHeader->mDataSize < TSize, "Invalid! Size");
		if (GetUsingSize() < sizeof(CBufferHeader) + aHeader->mDataSize)
			return nullptr;

		LB_ASSERT(aLastIndex < static_cast<int>(GetBufferSize()), "Wrong Index!");

		char* aData = nullptr;
		if (aReadIndex + static_cast<int>(aHeader->mDataSize) > aLastIndex + 1)
		{
			int aMaxIndex = aReadIndex + aHeader->mDataSize;
			int aCopySize = (aLastIndex - aReadIndex + 1);
			int aRestSize = (static_cast<int>(aHeader->mDataSize) - aCopySize);
			LB_ASSERT(aRestSize > 0, "Wrong Size!");

			::memcpy_s(__mRestBuffer, TMaxDataSize + sizeof(CBufferHeader), reinterpret_cast<const void*>(__mBuffer + aReadIndex), aCopySize);
			::memcpy_s(__mRestBuffer + aCopySize, TMaxDataSize + sizeof(CBufferHeader) - aCopySize, reinterpret_cast<const void*>(__mBuffer), aRestSize);

			aData		= __mRestBuffer;
			aReadIndex	= aRestSize;

			if (aPassIndex != -1)
				__mPassIndex = -1;
		}
		else
		{
			aData		= __mBuffer + aReadIndex;
			aReadIndex += aHeader->mDataSize;

			if (aReadIndex == aLastIndex + 1)
			{
				aReadIndex = 0;

				if (aPassIndex != -1)
					__mPassIndex = -1;
			}

			LB_ASSERT(aReadIndex <= aLastIndex, "Wrong Index");
		}

		{
			std::unique_lock<CLocker> aLocker(__mLocker);
			__mReadIndex = aReadIndex;
			__mUseSize	-= aHeader->mDataSize + sizeof(CBufferHeader);
			std::cout << "Read : " << __mReadIndex << " Size : " << aHeader->mDataSize + sizeof(CBufferHeader) << " " << aPassIndex << std::endl;
		}

		CheckBufferValid();
		LB_ASSERT(aData[0] == 1, "Wrong!");
		return aData;
	}

	template<Size TSize, Size TMaxDataSize>
	Size CBuffer<TSize, TMaxDataSize>::GetUsingSize() const
	{
		return __mUseSize;
	}

	template<Size TSize, Size TMaxDataSize>
	Size CBuffer<TSize, TMaxDataSize>::GetUsableSize() const
	{
		return GetBufferSize() - __mUseSize;
	}

	template<Size TSize, Size TMaxDataSize>
	constexpr Size CBuffer<TSize, TMaxDataSize>::GetBufferSize() const
	{
		static_assert(TSize > 0);
		return TSize;
	}

	template<Size TSize, Size TMaxDataSize>
	constexpr Size CBuffer<TSize, TMaxDataSize>::GetMaxDataSize() const
	{
		static_assert(TMaxDataSize > 0);
		return TMaxDataSize;
	}
}