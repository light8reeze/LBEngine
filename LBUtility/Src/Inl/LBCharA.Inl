namespace LBNet
{/*
	template<, Size TCharSize>
	inline void CChar<char, TCharSize>::SetStr(const char* pMsg)
	{
		bool bResult = StrCopy(__mChar, pMsg);
		LB_ASSERT(bResult, "CChar SetStr Fail");
		__mStrSize = GetStrLength(__mChar, TCharSize);
		LB_ASSERT(__mStrSize <= TCharSize, "Invalid Size");
	}

	template<, Size TCharSize>
	inline void CChar<char, TCharSize>::SetStr(const wchar_t* pMsg)
	{
		std::string str = WStrToStr(pMsg, TCharSize);
		bool bResult = StrCopy(__mChar, str.c_str());
		LB_ASSERT(bResult, "CChar SetStr Fail");
		__mStrSize = GetStrLength(__mChar, TCharSize);
		LB_ASSERT(__mStrSize <= TCharSize, "Invalid Size");
	}

	template<, Size TCharSize>
	inline void CChar<char, TCharSize>::SetStr(char pMsg)
	{
		if (pMsg == '\0')
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
	inline void CChar<char, TCharSize>::SetStr(wchar_t pMsg)
	{
		std::string str = WStrToStr(&pMsg, 1);
		LB_ASSERT(str.length() < 2, "Invalid Char");

		if (str.length() == 0)
		{
			__mChar[0] = '\0';
			__mStrSize = 0;
		}
		else
		{
			__mChar[0] = str[0];
			__mStrSize = 1;
		}
	}

	template<, Size TCharSize>
	inline void CChar<char, TCharSize>::Append(const char* pMsg)
	{
		LB_ASSERT(TCharSize - __mStrSize >= 0, "Invalid Size");
		bool bResult = StrConcat(__mChar, pMsg);
		LB_ASSERT(bResult, "CChar Append Fail");
		__mStrSize = GetStrLength(__mChar, TCharSize);
		LB_ASSERT(__mStrSize <= TCharSize, "Invalid Size");
	}

	template<, Size TCharSize>
	inline void CChar<char, TCharSize>::Append(const wchar_t* pMsg)
	{
		LB_ASSERT(TCharSize - __mStrSize >= 0, "Invalid Size");

		std::string str = WStrToStr(pMsg, TCharSize);
		bool bResult = StrConcat(__mChar, str.c_str());
		LB_ASSERT(bResult, "CChar Append Fail");

		__mStrSize = GetStrLength(__mChar, TCharSize);
		LB_ASSERT(__mStrSize <= TCharSize, "Invalid Size");
	}

	template<, Size TCharSize>
	inline std::string CChar<char, TCharSize>::GetCStrA() const
	{
		std::string str(__mChar);
		return str;
	}

	template<, Size TCharSize>
	inline std::wstring CChar<char, TCharSize>::GetCStrW() const
	{
		std::wstring str = StrToWStr(__mChar, TCharSize);
		return str;
	}

	template<, Size TCharSize>
	inline constexpr ECharMode CChar<char, TCharSize>::GetCharMode() const
	{
		return ECharMode::eMBCS;
	}
	
	template<, Size TCharSize>
	using CCharArrA = CChar<char, TCharSize>;
	using CCharA = CChar<char>;*/
}