namespace LBNet
{
#pragma region CLogBuffer
	template<typename TType>
	void CLogBuffer::PushLogData(TType& pData)
	{
		LB_ASSERT(__mUseSize < eSzLogMsg, "Error!");

		if (__mUseSize + sizeof(TType) >= eSzLogMsg)
			return;

		TType* aDataBuffer = reinterpret_cast<TType*>(__mBuffer + __mUseSize);
		(*aDataBuffer) = pData;
		__mUseSize += sizeof(TType);
	}

	template<typename TType>
	void CLogBuffer::PushLogData(TType&& pData)
	{
		LB_ASSERT(__mUseSize < eSzLogMsg, "Error!");

		if (__mUseSize + sizeof(TType) >= eSzLogMsg)
			return;

		TType* aDataBuffer = reinterpret_cast<TType*>(__mBuffer + __mUseSize);
		(*aDataBuffer) = std::move(pData);
		__mUseSize += sizeof(TType);
	}

	template<typename TType, Size TSize>
	void CLogBuffer::PushLogData(TType (&pData)[TSize])
	{
		using NonConstDataType = std::remove_const_t<TType>;
		LB_ASSERT(__mUseSize < eSzLogMsg, "Error!");

		if (__mUseSize + (sizeof(TType) * TSize) >= eSzLogMsg)
			return;

		NonConstDataType* aDataBuffer = reinterpret_cast<NonConstDataType*>(__mBuffer + __mUseSize);
		std::copy(pData, pData + TSize, aDataBuffer);
		__mUseSize += (sizeof(TType) * TSize);
	}

	template<typename TType, Size TSize>
	void CLogBuffer::PushLogData(TType (&&pData)[TSize])
	{
		using NonConstDataType = std::remove_const_t<TType>;
		LB_ASSERT(__mUseSize < eSzLogMsg, "Error!");

		if (__mUseSize + (sizeof(TType) * TSize) >= eSzLogMsg)
			return;

		NonConstDataType* aDataBuffer = reinterpret_cast<NonConstDataType*>(__mBuffer + __mUseSize);
		std::move(pData, pData + TSize, aDataBuffer);
		__mUseSize += (sizeof(TType) * TSize);
	}
#pragma endregion CLogBuffer

#pragma region CLogger
	template<typename TArgs>
	CLogger& CLogger::operator<<(TArgs&& pData)
	{
		if (_mLogBuffer != nullptr)
			_mLogBuffer->PushLogData(std::forward<TArgs>(pData));

		return (*this);
	}
#pragma endregion CLogger
}