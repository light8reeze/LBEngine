#pragma once

namespace LBNet
{
	template<typename TCharSet>
	inline CString<TCharSet>::CString() : __mStr()
	{
		static_assert((std::is_same<TCharSet, char>::value || std::is_same<TCharSet, wchar_t>::value));
	}

	template<typename TCharSet>
	inline CString<TCharSet>::CString(const CString<TCharSet>& pString)
		: __mStr(pString.GetString()), __mCharMode(pString.GetCharMode())
	{
	}

	template<typename TCharSet>
	inline CString<TCharSet>::CString(CString<TCharSet>&& pString) 
		: __mStr(std::move(pString.GetString())), __mCharMode(std::move(pString.GetCharMode()))
	{
	}

	template<typename TCharSet>
	template<typename TRCharSet>
	inline CString<TCharSet>::CString(const CString<TRCharSet>& pString) : __mStr()
	{
		operator=(pString);
	}

	template<typename TCharSet>
	template<typename TRCharSet>
	inline CString<TCharSet>::CString(const TRCharSet pString) : __mStr()
	{
		CString();
		operator=(pString);
	}

	template<typename TCharSet>
	inline CString<TCharSet>::~CString()
	{
	}

	template<typename TCharSet>
	template<typename TRCharSet>
	inline CString<TCharSet>& CString<TCharSet>::operator=(const CString<TRCharSet>& pRvalue)
	{
		if (IsSameAddress(this, &pRvalue))
			return (*this);

		return operator=(pRvalue.GetCStr());
	}

	template<typename TCharSet>
	inline CString<TCharSet>& CString<TCharSet>::operator=(CString<TCharSet>&& pRvalue)
	{
		__mStr = std::move(pRvalue.GetString());
		return (*this);
	}

	template<typename TCharSet>
	template<typename TRCharSet>
	inline CString<TCharSet>& CString<TCharSet>::operator+=(const CString<TRCharSet>& pRvalue)
	{
		return operator+=(pRvalue.GetCStr());
	}

	template<typename TCharSet>
	template<typename TRCharSet>
	inline CString<TCharSet> CString<TCharSet>::operator+(const CString<TRCharSet>& pRvalue)
	{
		CString<TCharSet> cResult(this->GetCStr());
		cResult += pRvalue.GetCStr();
		return cResult;
	}

	template<typename TCharSet>
	inline CString<TCharSet> CString<TCharSet>::operator+(const char* pRvalue)
	{
		CString<TCharSet> cResult(this->GetCStr());
		cResult += pRvalue;
		return cResult;
	}

	template<typename TCharSet>
	inline CString<TCharSet> CString<TCharSet>::operator+(const wchar_t* pRvalue)
	{
		CString<TCharSet> cResult(this->GetCStr());
		cResult += pRvalue;
		return cResult;
	}

	template<typename TCharSet>
	inline TCharSet& CString<TCharSet>::operator[](int pIndex)
	{
		if (pIndex >= GetLength() || pIndex < 0)
			throw std::out_of_range("CString index Out of range");

		return __mStr[pIndex];
	}

	template<typename TCharSet>
	inline typename CString<TCharSet>::CBasicString& CString<TCharSet>::GetString()
	{
		return __mStr;
	}

	template<typename TCharSet>
	inline typename const CString<TCharSet>::CBasicString& CString<TCharSet>::GetString() const
	{
		return __mStr;
	}

	template<typename TCharSet>
	inline const TCharSet* CString<TCharSet>::GetCStr() const
	{
		return __mStr.c_str();
	}

	template<typename TCharSet>
	inline std::wstring CString<TCharSet>::GetStringW()
	{
		return (__mCharMode == ECharMode::eUnicode) ? __mStr : StrToWStr(__mStr);
	}

	template<typename TCharSet>
	inline const std::wstring CString<TCharSet>::GetStringW() const
	{
		return const_cast<const std::wstring>(GetStringW());
	}

	template<typename TCharSet>
	inline std::string CString<TCharSet>::GetStringA()
	{
		return (__mCharMode == ECharMode::eMBCS) ? __mStr : WStrToStr(__mStr);
	}

	template<typename TCharSet>
	inline const std::string CString<TCharSet>::GetStringA() const
	{
		return const_cast<const std::string>(GetStringA());
	}

	template<typename TCharSet>
	inline int CString<TCharSet>::GetLength() const
	{
		return __mStr.length();
	}
}