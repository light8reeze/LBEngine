/**
	@file	LBChar.h
	@bfief	LBUtillity의 문자 관련 클래스 정의
	@date	2019-02-25
	@auther Light8reeze(light8reeze@gmail.com)
	@todo	Char클래스 추후에 완성할것
*/
#pragma once
#include "LBCharBase.h"

namespace LBNet
{
	//Desc : 정적 문자열클래스 TCharSet에 Char셋 타입을 설정한다.
	//		기본 타입은 TChar(프로젝트에 맞춤)이다.
	//Parm : TCharSet TCHAR	 = 문자열 타입(char, wchar_t)
	//		 Size TCharSize = 문자의 크기(글자수)
	//Warn : 1. 사용할 Char셋(TCharSet)과 다른 Char셋과 혼용하여사용 가능하지만 
	//		이동, 대입, 복사, 반환 등에서 변환과정이 추가되어 
	//		비 효율적이므로 되도록 혼용하여 사용하지 않는다.
	//		 2. TCharSet에 char, wchar_t타입 이외의 타입으로 설정시
	//		컴파일 에러가 발생한다.
	//		 3. operator <<은 미구현으로 char*를 받아 출력한다.
	//		 4. 이동 연산은 같은 Char셋, 크기의 타입끼리만 지원된다.(이동연산 추후 구현)
	//TODO : 이동연산자 구현
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


	//Desc : 정적 Char클래스의 배열 클래스 정의
	template<Size TCharSize>
	using CCharArrT = CChar<TChar, TCharSize>;

	//Desc : 정적 Char클래스의 정의
	using CCharT = CChar<TChar>;
}

#include "LBChar.Inl"
#include "LBCharA.Inl"
#include "LBCharW.Inl"