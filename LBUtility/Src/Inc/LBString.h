/**
	@file	LBString.h
	@bfief	LBUtillity의 문자열 클래스 정의
	@date	2019-02-27
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBCharBase.h"

namespace LBNet
{
	/**
		@bfief			정적 String클래스(힙 메모리를 사용하지 않는다.)
		@param TCharSet	문자열 타입(char, wchar_t)
		@param TSize	문자열 메모리 크기
		@warning		문자열 대입, 추가의 경우 정해진 크기까지만 들어간다.(TSize - 1)
		@date			2019-12-26
		@auther			light8reeze(light8reeze@gmail.com)
	*/
	template<typename TCharSet, Size TSize>
	class CString
	{
	public:
		using Type = TCharSet;

	public:
		CString();
		template<typename TString>
		CString(TString&& pRvalue);
		template<typename TString>
		CString(const TString& pRvalue);
		~CString() = default;

		template<typename TString>
		CString&	operator=(TString&& pRvalue);
		template<typename TString>
		CString&	operator+=(TString&& pRvalue);
		template<typename TString>
		CString		operator+(TString&& pRvalue);

		void		Assign(TCharSet*&& pStr);
		void		Assign(const TCharSet*& pStr);
		template<Size TRSize>
		void		Assign(CString<TCharSet, TRSize>&& pRvalue);
		template<Size TRSize>
		void		Assign(const CString<TCharSet, TRSize>& pRvalue);
		void		Assign(std::basic_string<TCharSet>&& pRvalue);
		void		Assign(const std::basic_string<TCharSet>& pRvalue);
		template<Size TNewSize>
		void		Assign(TCharSet(&&pRvalue)[TNewSize]);
		template<Size TNewSize>
		void		Assign(const TCharSet(&pRvalue)[TNewSize]);

		void		Append(const TCharSet*&& pStr);
		void		Append(const TCharSet*& pStr);
		template<Size TRSize>
		void		Append(CString<TCharSet, TRSize>&& pRvalue);
		template<Size TRSize>
		void		Append(const CString<TCharSet, TRSize>& pRvalue);
		void		Append(std::basic_string<TCharSet>&& pRvalue);
		void		Append(const std::basic_string<TCharSet>& pRvalue);
		template<Size TNewSize>
		void		Append(const TCharSet(&&pRvalue)[TNewSize]);
		template<Size TNewSize>
		void		Append(const TCharSet(&pRvalue)[TNewSize]);

		TCharSet&	operator[](Size pIndex);

		const TCharSet*		GetCStr() const;

		constexpr Size		GetMaxLength() const;
		Size				GetLength() const;

	private:
		TCharSet	__mStr[TSize];
		Size		__mUseSize;
	};

	/**
		@bfief			�޸� ���� ������ ��Ʈ�� Ŭ����.
						�޸� ���� �����͸� �ܺο��� �޾� ��� �����ϴ�.
		@param TCharSet	���ڿ� Ÿ��(char, wchar_t)
		@comment		std::string�� ����, ���� �� �� �޸𸮸� �̿��Ѵ�.
						�޸� ����ȭ�� ���� ���� ������ �޸𸮸� �̿��� string�� �����Ѵ�.
		@warning		String�� ����� �޸� ���۴� ȣ���ڰ� ���� �����Ѵ�.
		@date			2019-12-26
		@auther			light8reeze(light8reeze@gmail.com)
	*/
	template<typename TCharSet>
	class CBufferedString
	{
	public:
		using Type = TCharSet;

	public:
		CBufferedString();
		CBufferedString(CBufferedString&& pRvalue);
		CBufferedString(const CBufferedString& pRvalue);
		CBufferedString(TCharSet* pBuf, Size pBufSize);
		~CBufferedString() = default;

		void		AllocBuffer(TCharSet* pBuf, Size pBufSize);

		template<typename TString>
		CBufferedString&	operator=(TString&& pRvalue);
		template<typename TString>
		CBufferedString&	operator+=(TString&& pRvalue);
		template<typename TString>
		CBufferedString		operator+(TString&& pRvalue);

		void		Assign(TCharSet*&& pStr);
		void		Assign(const TCharSet*& pStr);
		void		Assign(CBufferedString<TCharSet>&& pRvalue);
		void		Assign(const CBufferedString<TCharSet>& pRvalue);
		void		Assign(std::basic_string<TCharSet>&& pRvalue);
		void		Assign(const std::basic_string<TCharSet>& pRvalue);
		template<Size TNewSize>
		void		Assign(TCharSet(&&pRvalue)[TNewSize]);
		template<Size TNewSize>
		void		Assign(const TCharSet(&pRvalue)[TNewSize]);

		void		Append(const TCharSet*&& pStr);
		void		Append(const TCharSet*& pStr);
		void		Append(CBufferedString<TCharSet>&& pRvalue);
		void		Append(const CBufferedString<TCharSet>& pRvalue);
		void		Append(std::basic_string<TCharSet>&& pRvalue);
		void		Append(const std::basic_string<TCharSet>& pRvalue);
		template<Size TNewSize>
		void		Append(const TCharSet(&&pRvalue)[TNewSize]);
		template<Size TNewSize>
		void		Append(const TCharSet(&pRvalue)[TNewSize]);

		TCharSet&	operator[](Size pIndex);

		const TCharSet*		GetCStr() const;

		Size				GetMaxLength() const;
		Size				GetLength() const;

	private:
		TCharSet*	__mStr;
		Size		__mMaxSize;
		Size		__mUseSize;
	};
}

#include "LBString.Inl"
