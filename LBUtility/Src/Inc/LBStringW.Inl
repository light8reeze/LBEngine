#pragma once

namespace LBNet
{
	using CStrintW = CString<wchar_t>;

	template<>
	inline CString<wchar_t>& CString<wchar_t>::operator=(const char* pRvalue)
	{
		if (IsSameAddress(this, &pRvalue))
			return (*this);

		__mStr = StrToWStr(pRvalue, GetStrLength(pRvalue, __mStr.max_size()));

		return (*this);
	}

	template<>
	inline CString<wchar_t>& CString<wchar_t>::operator=(const wchar_t* pRvalue)
	{
		if (IsSameAddress(this, &pRvalue))
			return (*this);

		__mStr = pRvalue;

		return (*this);
	}

	template<>
	inline CString<wchar_t>& CString<wchar_t>::operator+=(const char* pRvalue)
	{
		CBasicString&& strCpy = StrToWStr(pRvalue, GetStrLength(pRvalue, __mStr.max_size()));
		__mStr += strCpy;

		return (*this);
	}

	template<>
	inline CString<wchar_t>& CString<wchar_t>::operator+=(const wchar_t* pRvalue)
	{
		__mStr += pRvalue;

		return (*this);
	}

	template<>
	inline constexpr ECharMode CString<wchar_t>::GetCharMode() const
	{
		return ECharMode::eUnicode;
	}
}