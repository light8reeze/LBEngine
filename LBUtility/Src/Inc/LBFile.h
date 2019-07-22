/**
	@file	LBLogger.h
	@brief	LBUtillity�� �αװ��� ���
	@date	2019-07-20
	@auther Light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBUtility.h"
#include <fstream>
#include <iostream>
#include <utility>
#include <type_traits>
#include <functional>

namespace LBNet
{
	/**
		@brief		����IO Ŭ����
		@warnning	��Ƽ����Ʈ �ڵ� 
		@date		2019-07-20
		@auther		Light8reeze(light8reeze@gmail.com)
	*/
	class LBU_EXPORT CFile
	{
	private:
		using __EndLine = CFile& (*)(CFile&);
		using __OFStream = std::ofstream;
		using __IFStream = std::ifstream;

	public:
		CFile();
		template<typename TString>
		CFile(TString&& pStr);
		~CFile();

		template<typename TString>
		bool OpenFile(TString&& pStr);
		template<typename TArgs>
		CFile& operator>>(TArgs& pArgs) const;
		template<typename TArgs>
		CFile& operator<<(TArgs pArgs);

		bool IsOpen();

	public:
		static CFile& endl(CFile& out)
		{
			out << "\n";
			return out;
		}

	private:
		__IFStream __mIStream;
		__OFStream __mOStream;
	};
}

#include "LBFile.Inl"