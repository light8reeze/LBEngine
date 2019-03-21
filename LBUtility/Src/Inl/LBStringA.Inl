#pragma once

namespace LBNet
{
	using CStringA = CString<char>;

	template<>
	inline CString<char>& CString<char>::operator=(const char* pRvalue)
	{
		if (IsSameAddress(this, &pRvalue))
			return (*this);

		__mStr = pRvalue;

		return (*this);
	}

	template<>
	inline CString<char>& CString<char>::operator=(const wchar_t* pRvalue)
	{
		if (IsSameAddress(this, &pRvalue))
			return (*this);

		__mStr = WStrToStr(pRvalue, ::lstrlenW(pRvalue));

		return (*this);
	}

	template<>
	inline CString<char>& CString<char>::operator+=(const char* pRvalue)
	{
		__mStr += pRvalue;
		return (*this);
	}

	template<>
	inline CString<char>& CString<char>::operator+=(const wchar_t* pRvalue)
	{
		CBasicString&& strCpy = WStrToStr(pRvalue, GetStrLength(pRvalue, __mStr.max_size()));
		__mStr += strCpy;

		return (*this);
	}

	template<>
	inline constexpr ECharMode CString<char>::GetCharMode() const
	{
		return ECharMode::eMBCS;
	}
}