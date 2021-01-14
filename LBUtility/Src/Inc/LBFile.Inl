namespace LBNet
{
	CFile::CFile() : __mIStream(), __mOStream()
	{
	}

	template<typename TString>
	CFile::CFile(TString&& pStr) : __mIStream(), __mOStream()
	{
		OpenFile(std::forward<TString>(pStr));
	}

	CFile::~CFile()
	{
		if (__mIStream.is_open())
			__mIStream.close();

		if (__mOStream.is_open())
			__mOStream.close();
	}

	template<typename TString>
	bool CFile::OpenFile(TString&& pStr)
	{
		__mIStream.open(std::forward<TString>(pStr));
		__mOStream.open(std::forward<TString>(pStr), std::ios::app);

		return IsOpen();
	}

	template<typename TArgs>
	CFile& CFile::operator>>(TArgs& pArgs) const
	{
		__mIStream >> pArgs;
		return *this;
	}

	template<typename TArgs>
	CFile& CFile::operator<<(TArgs pArgs)
	{
		__mOStream << pArgs;
		return *this;
	}

	template<>
	CFile& CFile::operator<<(CFile::__EndLine pArgs)
	{
		return (pArgs)(*this);
	}

	bool CFile::IsOpen()
	{
		return (__mIStream.is_open() && __mOStream.is_open());
	}
}
