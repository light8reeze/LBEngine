/**
	@file LBString.h
	@bfief LBUtillity�� ���ڿ� Ŭ���� ����
	@date	2019-02-27
	@auther Light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBCharBase.h"

namespace LBNet
{
	/**
		@bfief			LBUtility�� ���� StringŬ����
		@param TCharSet	���ڿ� Ÿ��(char, wchar_t)
		@date			2019-02-27
		@auther			Light8reeze(light8reeze@gmail.com)
		@warning		1. ����� Char��(TCharSet)�� �ٸ� Char�°� ȥ���Ͽ���� ���������� 
						�̵�, ����, ����, ��ȯ ��� ��ȯ������ �߰��Ǿ� 
						�� ȿ�����̹Ƿ� �ǵ��� ȥ���Ͽ� ������� �ʴ´�.
						2. TCharSet�� char, wchar_tŸ�� �̿��� Ÿ������ ������
						������ ������ �߻��Ѵ�.
						3. operator <<�� �̱������� char*�� �޾� ����Ѵ�.
						4. �̵� ������ ���� Char��, ũ���� Ÿ�Գ����� �����ȴ�.(�̵����� ���� ����)
		@todo			�̵������� ����, CString ���ø� Ư��ȭ ��Ű��
	*/
	template<typename TCharSet = TChar>
	class CString final
	{
	public:
		using CBasicString	= std::basic_string<TCharSet>;

	public:
		CString();
		template<typename TRCharSet>
		CString(const CString<TRCharSet>& pString);
		template<typename TRCharSet>
		CString(const TRCharSet pString);
		CString(const CString<TCharSet>& pString);
		~CString();

		template<typename TRCharSet>
		CString& operator=(const CString<TRCharSet>& pRvalue);
		CString& operator=(const char* pRvalue);
		CString& operator=(const wchar_t* pRvalue);

		template<typename TRCharSet>
		CString& operator+=(const CString<TRCharSet>& pRvalue);
		CString& operator+=(const char* pRvalue);
		CString& operator+=(const wchar_t* pRvalue);

		template<typename TRCharSet>
		CString operator+(const CString<TRCharSet>& pRvalue);
		CString operator+(const char* pRvalue);
		CString operator+(const wchar_t* pRvalue);

		TCharSet& operator[](int pIndex);

		CBasicString&			GetString();
		const CBasicString&		GetString() const;
		const TCharSet*			GetCStr() const;

		std::wstring			GetStringW();
		const std::wstring		GetStringW() const;
		std::string				GetStringA();
		const std::string		GetStringA() const;

		int					GetLength() const;
		constexpr ECharMode	GetCharMode() const;
	
	private:
		CBasicString	__mStr;
	};

	using CStringT	= CString<TChar>;
}

#include "LBString.Inl"
#include "LBStringA.Inl"
#include "LBStringW.Inl"