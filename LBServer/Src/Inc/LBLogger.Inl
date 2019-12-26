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

	template <>
	void CLogBuffer::PushLogData<const char*>(const char*& pData)
	{
		LB_ASSERT(__mUseSize < eSzLogMsg, "Error!");

		Size aLength = static_cast<Size>(std::strlen(pData));
		if (__mUseSize + aLength >= eSzLogMsg)
			return;

		char* aDataBuffer = reinterpret_cast<char*>(__mBuffer + __mUseSize);
		std::copy(pData, pData + aLength, aDataBuffer);
		__mUseSize += aLength;
	}

	template <>
	void CLogBuffer::PushLogData<const char*>(const char*&& pData)
	{
		LB_ASSERT(__mUseSize < eSzLogMsg, "Error!");

		Size aLength = static_cast<Size>(std::strlen(pData));
		if (__mUseSize + aLength >= eSzLogMsg)
			return;

		char* aDataBuffer = reinterpret_cast<char*>(__mBuffer + __mUseSize);
		std::move(pData, pData + aLength, aDataBuffer);
		__mUseSize += aLength;
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

#pragma region CConsoleLog
	template<typename TArgs, typename TIsScalar>
	CConsoleLog& CConsoleLog::operator<<(TArgs&& pData)
	{
		return (__PushLogImpl(pData, TIsScalar()));
	}

	template<typename TArgs>
	CConsoleLog& CConsoleLog::__PushLogImpl(TArgs&& pData, std::true_type)
	{
		std::string aScalarToStr(std::to_string(pData));
		CLogger::operator<<(aScalarToStr.c_str());
		
		return (*this);
	}

	template<typename TArgs>
	CConsoleLog& CConsoleLog::__PushLogImpl(TArgs&& pData, std::false_type)
	{
		CLogger::operator<<(pData);
		
		return (*this);
	}
#pragma endregion CConsoleLog
}