/**
	@file	LBChar.h
	@bfief	LBUtillity�� ���� ���� Ŭ���� ����
	@date	2019-02-25
	@auther Light8reeze(light8reeze@gmail.com)
	@todo	CharŬ���� ���Ŀ� �ϼ��Ұ�
*/
#pragma once
#include "LBCharBase.h"

namespace LBNet
{
	//Desc : ���� ���ڿ�Ŭ���� TCharSet�� Char�� Ÿ���� �����Ѵ�.
	//		�⺻ Ÿ���� TChar(������Ʈ�� ����)�̴�.
	//Parm : TCharSet TCHAR	 = ���ڿ� Ÿ��(char, wchar_t)
	//		 Size TCharSize = ������ ũ��(���ڼ�)
	//Warn : 1. ����� Char��(TCharSet)�� �ٸ� Char�°� ȥ���Ͽ���� ���������� 
	//		�̵�, ����, ����, ��ȯ ��� ��ȯ������ �߰��Ǿ� 
	//		�� ȿ�����̹Ƿ� �ǵ��� ȥ���Ͽ� ������� �ʴ´�.
	//		 2. TCharSet�� char, wchar_tŸ�� �̿��� Ÿ������ ������
	//		������ ������ �߻��Ѵ�.
	//		 3. operator <<�� �̱������� char*�� �޾� ����Ѵ�.
	//		 4. �̵� ������ ���� Char��, ũ���� Ÿ�Գ����� �����ȴ�.(�̵����� ���� ����)
	//TODO : �̵������� ����
	//Auther : Light8reeze
	template<typename TCharSet = TChar, Size TCharSize = 1>
	class CChar final
	{
	public:
		CChar();
		template<typename TRCharSet, Size TRCharSize>
		CChar(const CChar<TRCharSet, TRCharSize>& pChar);
		template<typename TRCharSet>
		CChar(const TRCharSet* pChar);
		template<typename TRCharSet>
		CChar(TRCharSet pChar);
		//CChar(TCharSet*&& pChar);

		template<typename TRCharSet, Size TRCharSize>
		CChar& operator=(const CChar<TRCharSet, TRCharSize>& pChar);
		template<typename TRCharSet>
		CChar& operator=(const TRCharSet* pRvalue);
		template<typename TRCharSet>
		CChar& operator=(TRCharSet pRvalue);
		//template<typename TRCharSet, Size TRCharSize>
		//CChar& operator=(CChar<TRCharSet, TRCharSize>&& pRvalue);

		template<typename TRCharSet, Size TRCharSize>
		CChar& operator+=(const CChar<TRCharSet, TRCharSize>& pChar);
		template<typename TRCharSet>
		CChar& operator+=(const TRCharSet* pRvalue);
		template<typename TRCharSet>
		CChar& operator+=(TRCharSet pRvalue);

		template<typename TRCharSet, Size TRCharSize>
		CChar operator+(const CChar<TRCharSet, TRCharSize>& pRvalue);
		template<typename TRCharSet>
		CChar operator+(const TRCharSet* pRvalue);
		template<typename TRCharSet>
		CChar operator+(TRCharSet pRvalue);

		TCharSet& operator[](int pIndex);

		void				SetStr(const char* pMsg);
		void				SetStr(const wchar_t* pMsg);
		void				SetStr(char pMsg);
		void				SetStr(wchar_t pMsg);

		void				Append(const char* pMsg);
		void				Append(const wchar_t* pMsg);

		Size				GetLength() const;
		TCharSet*			GetCStr();
		const TCharSet*		GetCStr() const;
		std::string			GetCStrA() const;
		std::wstring		GetCStrW() const;
		constexpr Size		GetTSize() const;
		constexpr ECharMode	GetCharMode() const;

	private:
		TCharSet	__mChar[TCharSize];
		Size		__mStrSize;
	};


	//Desc : ���� CharŬ������ �迭 Ŭ���� ����
	template<Size TCharSize>
	using CCharArrT = CChar<TChar, TCharSize>;

	//Desc : ���� CharŬ������ ����
	using CCharT = CChar<TChar>;
}

#include "LBChar.Inl"
#include "LBCharA.Inl"
#include "LBCharW.Inl"