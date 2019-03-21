namespace LBNet
{/*
	template<, Size TCharSize>
	inline void CChar<wchar_t, TCharSize>::SetStr(const char* pMsg)
	{
		std::wstring str = StrToWStr(pMsg, TCharSize);
		bool bResult = StrCopy(__mChar, str.c_str());
		LB_ASSERT(bResult, "CChar SetStr Fail");
		__mStrSize = GetStrLength(__mChar, TCharSize);
		LB_ASSERT(__mStrSize <= TCharSize, "Invalid Size");
	}

	template<, Size TCharSize>
	inline void CChar<wchar_t, TCharSize>::SetStr(const wchar_t* pMsg)
	{
		bool bResult = StrCopy(__mChar, pMsg);
		LB_ASSERT(bResult, "CChar SetStr Fail");
		__mStrSize = GetStrLength(__mChar, TCharSize);
		LB_ASSERT(__mStrSize <= TCharSize, "Invalid Size");
	}

	template<, Size TCharSize>
	inline void CChar<wchar_t, TCharSize>::SetStr(char pMsg)
	{
		std::wstring str = StrToWStr(&pMsg, 1);
		LB_ASSERT(str.length() < 2, "Invalid Char");

		if (str.length() == 0)
		{
			__mChar[0] = L'\0';
			__mStrSize = 0;
		}
		else
		{
			__mChar[0] = str[0];
			__mStrSize = 1;
		}
	}

	template<, Size TCharSize>
	inline void CChar<wchar_t, TCharSize>::SetStr(wchar_t pMsg)
	{
		if (pMsg == L'\0')
		{
			__mChar[0] = pMsg;
			__mStrSize = 0;
		}
		else
		{
			__mChar[0] = pMsg;
			__mStrSize = 1;
		}
	}

	template<, Size TCharSize>
	inline void CChar<wchar_t, TCharSize>::Append(const char* pMsg)
	{
		LB_ASSERT(TCharSize - __mStrSize >= 0, "Invalid Size");

		std::wstring str = StrToWStr(pMsg, TCharSize);
		bool bResult = StrConcat(__mChar, str.c_str());
		LB_ASSERT(bResult, "CChar Append Fail");

		__mStrSize = GetStrLength(__mChar, TCharSize);
		LB_ASSERT(__mStrSize <= TCharSize, "Invalid Size");
	}

	template<, Size TCharSize>
	inline void CChar<wchar_t, TCharSize>::Append(const wchar_t* pMsg)
	{
		LB_ASSERT(TCharSize - __mStrSize >= 0, "Invalid Size");
		bool bResult = StrConcat(__mChar, pMsg);
		LB_ASSERT(bResult, "CChar Append Fail");
		__mStrSize = GetStrLength(__mChar, TCharSize);
		LB_ASSERT(__mStrSize <= TCharSize, "Invalid Size");
	}

	template<, Size TCharSize>
	inline std::string CChar<wchar_t, TCharSize>::GetCStrA() const
	{
		std::string str = WStrToStr(__mChar, TCharSize);
		return str;
	}

	template<, Size TCharSize>
	inline std::wstring CChar<wchar_t, TCharSize>::GetCStrW() const
	{
		std::wstring str(__mChar);
		return str;
	}

	template<, Size TCharSize>
	inline constexpr ECharMode CChar<wchar_t, TCharSize>::GetCharMode() const
	{
		return ECharMode::eUnicode;
	}

	template<, Size TCharSize>
	using CCharArrW = CChar<wchar_t, TCharSize>;
	using CCharW = CChar<wchar_t>;
	*/
}