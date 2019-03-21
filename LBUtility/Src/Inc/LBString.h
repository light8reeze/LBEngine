/**
	@file LBString.h
	@bfief LBUtillity의 문자열 클래스 정의
	@date	2019-02-27
	@auther Light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBCharBase.h"

namespace LBNet
{
	/**
		@bfief			LBUtility의 동적 String클래스
		@param TCharSet	문자열 타입(char, wchar_t)
		@date			2019-02-27
		@auther			Light8reeze(light8reeze@gmail.com)
		@warning		1. 사용할 Char셋(TCharSet)과 다른 Char셋과 혼용하여사용 가능하지만 
						이동, 대입, 복사, 반환 등에서 변환과정이 추가되어 
						비 효율적이므로 되도록 혼용하여 사용하지 않는다.
						2. TCharSet에 char, wchar_t타입 이외의 타입으로 설정시
						컴파일 에러가 발생한다.
						3. operator <<은 미구현으로 char*를 받아 출력한다.
						4. 이동 연산은 같은 Char셋, 크기의 타입끼리만 지원된다.(이동연산 추후 구현)
		@todo			이동연산자 구현, CString 템플릿 특수화 시키기
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