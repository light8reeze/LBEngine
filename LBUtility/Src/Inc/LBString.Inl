namespace LBNet
{
#pragma region CString
	template<typename TCharSet, Size TSize>
	CString<TCharSet, TSize>::CString() : __mStr(), __mUseSize(0)
	{
		std::fill(__mStr, __mStr + TSize, 0);
	}

	template<typename TCharSet, Size TSize>
	template<typename TString>
	CString<TCharSet, TSize>::CString(TString&& pRvalue)
		: __mStr(), __mUseSize(0)
	{
		Assign(std::forward<TString>(pRvalue));
	}

	template<typename TCharSet, Size TSize>
	template<typename TString>
	CString<TCharSet, TSize>::CString(const TString& pRvalue)
		: __mStr(), __mUseSize(0)
	{
		Assign(pRvalue);
	}

	template<typename TCharSet, Size TSize>
	template<typename TString>
	CString<TCharSet, TSize>&	CString<TCharSet, TSize>::operator=(TString&& pRvalue)
	{
		Assign(std::forward<TString>(pRvalue));
		return (*this);
	}

	template<typename TCharSet, Size TSize>
	template<typename TString>
	CString<TCharSet, TSize>&	CString<TCharSet, TSize>::operator+=(TString&& pRvalue)
	{
		Append(std::forward<TString>(pRvalue));
		return (*this);
	}

	template<typename TCharSet, Size TSize>
	template<typename TString>
	CString<TCharSet, TSize>	CString<TCharSet, TSize>::operator+(TString&& pRvalue)
	{
		CString aStr;
		aStr.Append(GetCStr());
		aStr.Append(pRvalue);

		return aStr;
	}

	template<typename TCharSet, Size TSize>
	void CString<TCharSet, TSize>::Assign(TCharSet*&& pStr)
	{
		if (pStr == nullptr)
			return;

		Size aLength = static_cast<Size>(StrLen(pStr, TSize - 1));
		std::move(pStr, pStr + aLength + 1, __mStr);
		__mStr[aLength] = '\0';
		__mUseSize = (aLength + 1);
	}

	template<typename TCharSet, Size TSize>
	void CString<TCharSet, TSize>::Assign(const TCharSet*& pStr)
	{
		if (pStr == nullptr)
			return;

		Size aLength = static_cast<Size>(StrLen(pStr, TSize - 1));
		std::copy(pStr, pStr + aLength + 1, __mStr);
		__mStr[aLength] = '\0';
		__mUseSize = (aLength + 1);
	}

	template<typename TCharSet, Size TSize>
	template<Size TRSize>
	void CString<TCharSet, TSize>::Assign(CString<TCharSet, TRSize>&& pRvalue)
	{
		if (IsSameAddress(this, &pRvalue))
			return;

		Assign(pRvalue.GetCStr());
	}

	template<typename TCharSet, Size TSize>
	template<Size TRSize>
	void CString<TCharSet, TSize>::Assign(const CString<TCharSet, TRSize>& pRvalue)
	{
		if (IsSameAddress(this, &pRvalue))
			return;

		Assign(pRvalue.GetCStr());
	}

	template<typename TCharSet, Size TSize>
	void CString<TCharSet, TSize>::Assign(std::basic_string<TCharSet>&& pRvalue)
	{
		Assign(static_cast<TCharSet*>(pRvalue.data()));
	}

	template<typename TCharSet, Size TSize>
	void CString<TCharSet, TSize>::Assign(const std::basic_string<TCharSet>& pRvalue)
	{
		Assign(pRvalue.data());
	}

	template<typename TCharSet, Size TSize>
	template<Size TNewSize>
	void CString<TCharSet, TSize>::Assign(TCharSet(&&pRvalue)[TNewSize])
	{
		Size aLength = std::min(TNewSize, TSize);
		std::move(pRvalue, pRvalue + aLength, __mStr);
		__mUseSize = aLength;
	}

	template<typename TCharSet, Size TSize>
	template<Size TNewSize>
	void CString<TCharSet, TSize>::Assign(const TCharSet(&pRvalue)[TNewSize])
	{
		Size aLength = std::min(TNewSize, TSize);
		std::copy(pRvalue, pRvalue + aLength, __mStr);
		__mUseSize = aLength;
	}

	template<typename TCharSet, Size TSize>
	void CString<TCharSet, TSize>::Append(const TCharSet*&& pStr)
	{
		if (pStr == nullptr)
			return;

		Size aLength = static_cast<Size>(StrLen(pStr, TSize - __mUseSize - 1));
		std::move(pStr, pStr + aLength, __mStr + __mUseSize - 1);
		__mUseSize += aLength;
	}

	template<typename TCharSet, Size TSize>
	void CString<TCharSet, TSize>::Append(const TCharSet*& pStr)
	{
		if (pStr == nullptr)
			return;

		Size aLength = static_cast<Size>(StrLen(pStr, TSize - __mUseSize));
		std::copy(pStr, pStr + aLength, __mStr + __mUseSize - 1);
		__mUseSize += aLength;
	}

	template<typename TCharSet, Size TSize>
	template<Size TRSize>
	void CString<TCharSet, TSize>::Append(CString<TCharSet, TRSize>&& pRvalue)
	{
		if (IsSameAddress(this, &pRvalue))
			return;

		Append(std::forward<const TCharSet*>(pRvalue.GetCStr()));
	}

	template<typename TCharSet, Size TSize>
	template<Size TRSize>
	void CString<TCharSet, TSize>::Append(const CString<TCharSet, TRSize>& pRvalue)
	{
		if (IsSameAddress(this, &pRvalue))
			return;

		Append(std::forward<const TCharSet*>(pRvalue.GetCStr()));
	}

	template<typename TCharSet, Size TSize>
	void CString<TCharSet, TSize>::Append(std::basic_string<TCharSet>&& pRvalue)
	{
		Append(std::forward<const TCharSet*>(pRvalue.data()));
	}

	template<typename TCharSet, Size TSize>
	void CString<TCharSet, TSize>::Append(const std::basic_string<TCharSet>& pRvalue)
	{
		Append(std::forward<const TCharSet*>(pRvalue.data()));
	}

	template<typename TCharSet, Size TSize>
	template<Size TNewSize>
	void CString<TCharSet, TSize>::Append(const TCharSet(&&pRvalue)[TNewSize])
	{
		Size aLength = std::min(TNewSize, TSize - __mUseSize);
		std::move(pRvalue, pRvalue + aLength, __mStr + __mUseSize - 1);
		__mUseSize += (aLength - 1);
	}

	template<typename TCharSet, Size TSize>
	template<Size TNewSize>
	void CString<TCharSet, TSize>::Append(const TCharSet(&pRvalue)[TNewSize])
	{
		Size aLength = std::min(TNewSize, TSize - __mUseSize);
		std::copy(pRvalue, pRvalue + aLength, __mStr + __mUseSize - 1);
		__mUseSize += (aLength - 1);
	}

	template<typename TCharSet, Size TSize>
	TCharSet& CString<TCharSet, TSize>::operator[](Size pIndex)
	{
		if (pIndex >= TSize)
			throw std::out_of_range("CString index Out of range");

		return __mStr[pIndex];
	}

	template<typename TCharSet, Size TSize>
	const TCharSet* CString<TCharSet, TSize>::GetCStr() const
	{
		return __mStr;
	}

	template<typename TCharSet, Size TSize>
	constexpr Size CString<TCharSet, TSize>::GetMaxLength() const
	{
		return TSize;
	}

	template<typename TCharSet, Size TSize>
	Size CString<TCharSet, TSize>::GetLength() const
	{
		return __mUseSize;
	}
#pragma endregion CString

#pragma region CBufferedString
	template<typename TCharSet>
	CBufferedString<TCharSet>::CBufferedString() : __mStr(nullptr), __mMaxSize(0), __mUseSize(0)
	{
	}

	template<typename TCharSet>
	CBufferedString<TCharSet>::CBufferedString(CBufferedString&& pRvalue)
		: __mStr(std::move(pRvalue.__mStr)), __mMaxSize(std::move(pRvalue.__mMaxSize)), 
		__mUseSize(std::move(pRvalue.__mUseSize))
	{
	}

	template<typename TCharSet>
	CBufferedString<TCharSet>::CBufferedString(const CBufferedString& pRvalue)
		: __mStr(pRvalue.__mStr), __mMaxSize(pRvalue.__mMaxSize), __mUseSize(pRvalue.__mUseSize)
	{
	}

	template<typename TCharSet>
	CBufferedString<TCharSet>::CBufferedString(TCharSet* pBuf, Size pBufSize)
		: __mStr(nullptr), __mMaxSize(0), __mUseSize(0)
	{
		AllocBuffer(pBuf, pBufSize);
	}

	template<typename TCharSet>
	void CBufferedString<TCharSet>::AllocBuffer(TCharSet* pBuf, Size pBufSize)
	{
		LB_ASSERT(pBuf != nullptr, "Error!");

		__mStr = pBuf;
		__mMaxSize = pBufSize;
		__mUseSize = 0;

		std::fill(__mStr, __mStr + __mMaxSize, 0);
	}

	template<typename TCharSet>
	template<typename TString>
	CBufferedString<TCharSet>&	CBufferedString<TCharSet>::operator=(TString&& pRvalue)
	{
		Assign(std::forward<TString>(pRvalue));
		return (*this);
	}

	template<typename TCharSet>
	template<typename TString>
	CBufferedString<TCharSet>&	CBufferedString<TCharSet>::operator+=(TString&& pRvalue)
	{
		Append(std::forward<TString>(pRvalue));
		return (*this);
	}

	template<typename TCharSet>
	template<typename TString>
	CBufferedString<TCharSet>	CBufferedString<TCharSet>::operator+(TString&& pRvalue)
	{
		CBufferedString aStr;
		aStr.Append(GetCStr());
		aStr.Append(pRvalue);

		return aStr;
	}

	template<typename TCharSet>
	void CBufferedString<TCharSet>::Assign(TCharSet*&& pStr)
	{
		if (pStr == nullptr || __mStr == nullptr)
			return;

		if (IsSameAddress(__mStr, pStr))
			return;

		Size aLength = static_cast<Size>(StrLen(pStr, GetMaxLength() - 1));
		std::move(pStr, pStr + aLength + 1, __mStr);
		__mStr[aLength] = '\0';
		__mUseSize = (aLength + 1);
	}

	template<typename TCharSet>
	void CBufferedString<TCharSet>::Assign(const TCharSet*& pStr)
	{
		if (pStr == nullptr || __mStr == nullptr)
			return;

		if (IsSameAddress(__mStr, const_cast<TCharSet*>(pStr)))
			return;

		Size aLength = static_cast<Size>(StrLen(pStr, GetMaxLength() - 1));
		std::copy(pStr, pStr + aLength + 1, __mStr);
		__mStr[aLength] = '\0';
		__mUseSize = (aLength + 1);
	}

	template<typename TCharSet>
	void CBufferedString<TCharSet>::Assign(CBufferedString<TCharSet>&& pRvalue)
	{
		if (IsSameAddress(this, &pRvalue))
			return;

		Assign(pRvalue.GetCStr());
	}

	template<typename TCharSet>
	void CBufferedString<TCharSet>::Assign(const CBufferedString<TCharSet>& pRvalue)
	{
		if (IsSameAddress(this, &pRvalue))
			return;

		Assign(pRvalue.GetCStr());
	}

	template<typename TCharSet>
	void CBufferedString<TCharSet>::Assign(std::basic_string<TCharSet>&& pRvalue)
	{
		Assign(static_cast<TCharSet*>(pRvalue.data()));
	}

	template<typename TCharSet>
	void CBufferedString<TCharSet>::Assign(const std::basic_string<TCharSet>& pRvalue)
	{
		Assign(pRvalue.data());
	}

	template<typename TCharSet>
	template<Size TNewSize>
	void CBufferedString<TCharSet>::Assign(TCharSet(&&pRvalue)[TNewSize])
	{
		if (__mStr == nullptr)
			return;

		Size aLength = std::min(TNewSize, GetMaxLength());
		std::move(pRvalue, pRvalue + aLength, __mStr);
		__mUseSize = aLength;
	}

	template<typename TCharSet>
	template<Size TNewSize>
	void CBufferedString<TCharSet>::Assign(const TCharSet(&pRvalue)[TNewSize])
	{
		if (__mStr == nullptr)
			return;

		Size aLength = std::min(TNewSize, GetMaxLength());
		std::copy(pRvalue, pRvalue + aLength, __mStr);
		__mUseSize = aLength;
	}

	template<typename TCharSet>
	void CBufferedString<TCharSet>::Append(const TCharSet*&& pStr)
	{
		if (pStr == nullptr || __mStr == nullptr)
			return;

		Size aLength = static_cast<Size>(StrLen(pStr, GetMaxLength() - __mUseSize - 1));
		std::move(pStr, pStr + aLength, __mStr + std::max(__mUseSize - 1, 0));
		__mUseSize += aLength;
	}

	template<typename TCharSet>
	void CBufferedString<TCharSet>::Append(const TCharSet*& pStr)
	{
		if (pStr == nullptr || __mStr == nullptr)
			return;

		Size aLength = static_cast<Size>(StrLen(pStr, GetMaxLength() - __mUseSize));
		std::copy(pStr, pStr + aLength, __mStr + std::max(__mUseSize - 1, 0));
		__mUseSize += aLength;
	}

	template<typename TCharSet>
	void CBufferedString<TCharSet>::Append(CBufferedString<TCharSet>&& pRvalue)
	{
		if (IsSameAddress(this, &pRvalue))
			return;

		Append(std::forward<const TCharSet*>(pRvalue.GetCStr()));
	}

	template<typename TCharSet>
	void CBufferedString<TCharSet>::Append(const CBufferedString<TCharSet>& pRvalue)
	{
		if (IsSameAddress(this, &pRvalue))
			return;

		Append(std::forward<const TCharSet*>(pRvalue.GetCStr()));
	}

	template<typename TCharSet>
	void CBufferedString<TCharSet>::Append(std::basic_string<TCharSet>&& pRvalue)
	{
		Append(std::forward<const TCharSet*>(pRvalue.data()));
	}

	template<typename TCharSet>
	void CBufferedString<TCharSet>::Append(const std::basic_string<TCharSet>& pRvalue)
	{
		Append(std::forward<const TCharSet*>(pRvalue.data()));
	}

	template<typename TCharSet>
	template<Size TNewSize>
	void CBufferedString<TCharSet>::Append(const TCharSet(&&pRvalue)[TNewSize])
	{
		if (__mStr == nullptr)
			return;

		Size aLength = std::min(TNewSize, GetMaxLength() - __mUseSize);
		std::move(pRvalue, pRvalue + aLength, __mStr + std::max(__mUseSize - 1, 0));
		__mUseSize += (aLength - 1);
	}

	template<typename TCharSet>
	template<Size TNewSize>
	void CBufferedString<TCharSet>::Append(const TCharSet(&pRvalue)[TNewSize])
	{
		if (__mStr == nullptr)
			return;

		Size aLength = std::min(TNewSize, GetMaxLength() - __mUseSize);
		std::copy(pRvalue, pRvalue + aLength, __mStr + std::max(__mUseSize - 1, 0));
		__mUseSize += (aLength - 1);
	}

	template<typename TCharSet>
	TCharSet& CBufferedString<TCharSet>::operator[](Size pIndex)
	{
		if (pIndex >= GetMaxLength())
			throw std::out_of_range("CString index Out of range");

		return __mStr[pIndex];
	}

	template<typename TCharSet>
	const TCharSet* CBufferedString<TCharSet>::GetCStr() const
	{
		return __mStr;
	}

	template<typename TCharSet>
	Size CBufferedString<TCharSet>::GetMaxLength() const
	{
		return __mMaxSize;
	}

	template<typename TCharSet>
	Size CBufferedString<TCharSet>::GetLength() const
	{
		return __mUseSize;
	}
#pragma endregion CBufferedString
}