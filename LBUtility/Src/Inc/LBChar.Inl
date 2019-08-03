namespace LBNet
{
	template<typename TCharSet, Size TCharSize>
	inline CChar<TCharSet, TCharSize>::CChar() : __mChar(), __mStrSize(0)
	{
		static_assert((std::is_same<TCharSet, char>::value || std::is_same<TCharSet, wchar_t>::value));
		static_assert(TCharSize > 0);
	}

	template<typename TCharSet, Size TCharSize>
	template<typename TRCharSet, Size TRCharSize>
	inline CChar<TCharSet, TCharSize>::CChar(const CChar<TRCharSet, TRCharSize>& pChar) : __mChar(), __mStrSize(0)
	{
		operator=(pChar);
	}

	template<typename TCharSet, Size TCharSize>
	template<typename TRCharSet>
	inline CChar<TCharSet, TCharSize>::CChar(const TRCharSet* pChar) : __mChar(), __mStrSize(0)
	{
		operator=(pChar);
	}

	template<typename TCharSet, Size TCharSize>
	template<typename TRCharSet>
	inline CChar<TCharSet, TCharSize>::CChar(TRCharSet pChar) : __mChar(), __mStrSize(0)
	{
		operator=(pChar);
	}

	template<typename TCharSet, Size TCharSize>
	template<typename TRCharSet, Size TRCharSize>
	inline CChar<TCharSet, TCharSize>& CChar<TCharSet, TCharSize>::operator=(const CChar<TRCharSet, TRCharSize>& pChar)
	{
		if (IsSameAddress(this, &pChar))
			return this;

		Size lowSize = (TCharSize > TRCharSize) ? TRCharSize : TCharSize;
		SetStr(pChar.GetCStr, lowSize);
	}

	template<typename TCharSet, Size TCharSize>
	template<typename TRCharSet>
	inline CChar<TCharSet, TCharSize>& CChar<TCharSet, TCharSize>::operator=(const TRCharSet* pRvalue)
	{
		if (IsSameAddress(this, &pChar))
			return (*this);

		Size strSize = GetStrLength(pRvalue, TCharSize);
		SetStr(pRvalue, strSize);
	}

	template<typename TCharSet, Size TCharSize>
	template<typename TRCharSet>
	inline CChar<TCharSet, TCharSize>& CChar<TCharSet, TCharSize>::operator=(TRCharSet pRvalue)
	{
		if (IsSameAddress(this, &pChar))
			return (*this);

		SetStr(pRvalue);
	}

	template<typename TCharSet, Size TCharSize>
	template<typename TRCharSet, Size TRCharSize>
	inline CChar<TCharSet, TCharSize>& CChar<TCharSet, TCharSize>::operator+=(const CChar<TRCharSet, TRCharSize>& pChar)
	{
		Size lowSize = (TCharSize > TRCharSize) ? TRCharSize : TCharSize;
		Append(pChar.GetCStr, lowSize);

		return (*this);
	}

	template<typename TCharSet, Size TCharSize>
	template<typename TRCharSet>
	inline CChar<TCharSet, TCharSize>& CChar<TCharSet, TCharSize>::operator+=(const TRCharSet* pChar)
	{
		Size strSize = GetStrLength(pRvalue, TCharSize);
		Append(pChar.GetCStr, strSize);

		return (*this);
	}

	template<typename TCharSet, Size TCharSize>
	template<typename TRCharSet>
	inline CChar<TCharSet, TCharSize>& CChar<TCharSet, TCharSize>::operator+=(TRCharSet pChar)
	{
		Append(&pChar, 1);

		return (*this);
	}

	template<typename TCharSet, Size TCharSize>
	template<typename TRCharSet, Size TRCharSize>
	inline CChar<TCharSet, TCharSize> CChar<TCharSet, TCharSize>::operator+(const CChar<TRCharSet, TRCharSize>& pRvalue)
	{
		CChar<TCharSet, TCharSize> cResult(this->GetStr());
		Size lowSize = (TCharSize > TRCharSize) ? TRCharSize : TCharSize;
		cResult.Append(pRvalue.GetCStr, lowSize);

		return cResult;
	}

	template<typename TCharSet, Size TCharSize>
	template<typename TRCharSet>
	inline CChar<TCharSet, TCharSize> CChar<TCharSet, TCharSize>::operator+(const TRCharSet* pRvalue)
	{
		CChar<TCharSet, TCharSize> cResult(this->GetStr());
		Size lowSize = (TCharSize > TRCharSize) ? TRCharSize : TCharSize;
		cResult.Append(pRvalue, lowSize);

		return cResult;
	}

	template<typename TCharSet, Size TCharSize>
	template<typename TRCharSet>
	inline CChar<TCharSet, TCharSize> CChar<TCharSet, TCharSize>::operator+(TRCharSet pRvalue)
	{
		CChar<TCharSet, TCharSize> cResult(this->GetStr());
		cResult.Append(pRvalue, 1);

		return cResult;
	}

	template<typename TCharSet, Size TCharSize>
	inline TCharSet& CChar<TCharSet, TCharSize>::operator[](int pIndex)
	{
		if (pIndex >= TCharSize || pIndex < 0)
			throw std::out_of_range("CChar Index Out of range!");

		return __mChar[pIndex];
	}

	template<typename TCharSet, Size TCharSize>
	inline TCharSet* CChar<TCharSet, TCharSize>::GetCStr()
	{
		return __mChar;
	}

	template<typename TCharSet, Size TCharSize>
	inline const TCharSet* CChar<TCharSet, TCharSize>::GetCStr() const
	{
		return const_cast<const TCharSet*>(GetCStr());
	}

	template<typename TCharSet, Size TCharSize>
	inline constexpr Size CChar<TCharSet, TCharSize>::GetTSize() const
	{
		return TCharSize;
	}

	template<typename TCharSet, Size TCharSize>
	inline Size CChar<TCharSet, TCharSize>::GetLength() const
	{
		return __mStrSize;
	}
}