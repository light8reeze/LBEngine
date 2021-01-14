﻿/**
	@file	LBCharBase.h
	@bfief	LBUtillity의 문자열에 필요한 상수, 함수등을 정의해놓은 파일
	@date	2019-02-25
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBUtility.h"
#include <string>
#ifdef _WIN32
#include <tchar.h>
#include <atlstr.h>
#endif //_WIN32

namespace LBNet
{
	#ifdef _UNICODE
	using TChar = wchar_t;
	#elif _MBCS
	using TChar = char;
	#else
	#error Using CharSet MBCS or Unicode(define _MBCS or _UNICODE)
	#endif //_UNICODE, _MBCS

	/**
		@brief Char셋 정의
	*/
	enum class ECharMode
	{
		eMBCS = 0,
		eUnicode,
		eNone
	};

	/**
		@brief 현재 프로젝트에서 지원하는 Char타입을 반환한다.
	*/
	constexpr ECharMode EProjectChar()
	{
		#ifdef _UNICODE
		return ECharMode::eUnicode;
		#elif _MBCS
		return ECharMode::eMBCS;
		#else
		#error Using CharSet MBCS or Unicode(define _MBCS or _UNICODE)
		#endif //_UNICODE, _MBCS
	}

#ifdef _WIN32
	inline std::string WStrToStr(const wchar_t* pPStr, int pNLength)
	{
		std::string resultStr;
		resultStr.reserve(pNLength);
		resultStr = CW2A(pPStr);
		return std::move(resultStr);
	}

	inline std::string WStrToStr(const std::wstring& pWStr)
	{
		return std::move(WStrToStr(pWStr.c_str(), static_cast<int>(pWStr.length())));
	}

	inline std::wstring StrToWStr(const char* pPStr, int pNLength)
	{
		std::wstring resultStr;
		resultStr.reserve(pNLength);
		resultStr = CA2W(pPStr);
		return std::move(resultStr);
	}

	inline std::wstring StrToWStr(const std::string& pStr)
	{
		return std::move(StrToWStr(pStr.c_str(), static_cast<int>(pStr.length())));
	}
#endif //_WIN32

	inline Size StrLen(const char* pChar, Size pMaxSize)
	{
		Size charSize = static_cast<Size>(::strnlen_s(pChar, static_cast<size_t>(pMaxSize)));
		LB_ASSERT(charSize >= 0, "Invalid Char");

		return charSize;
	}

	inline Size StrLen(const wchar_t* pChar, Size pMaxSize)
	{
		Size charSize = static_cast<Size>(::wcsnlen_s(pChar, static_cast<size_t>(pMaxSize)));
		LB_ASSERT(charSize >= 0, "Invalid Char");

		return charSize;
	}

	inline bool StrCopy(char* pDest, Size pDestSize, const char* pSrc)
	{
		int result = ::strcpy_s(pDest, static_cast<rsize_t>(pDestSize), pSrc);
		LB_ASSERT(result != 0, "strcpy_s Fail!");

		return (result == 0);
	}

	inline bool StrCopy(wchar_t* pDest, Size pDestSize, const wchar_t* pSrc)
	{
		int result = ::wcscpy_s(pDest, static_cast<rsize_t>(pDestSize), pSrc);
		LB_ASSERT(result != 0, "strcpy_s Fail!");

		return (result == 0);
	}

	template<Size TSize>
	inline bool StrCopy(char (&pDest)[TSize], const char* pSrc)
	{
		int result = ::strcpy_s(pDest, pSrc);
		LB_ASSERT(result != 0, "strcpy_s Fail!");

		return (result == 0);
	}

	template<Size TSize>
	inline bool StrCopy(wchar_t (&pDest)[TSize], const wchar_t* pSrc)
	{
		int result = ::wcscpy_s(pDest, pSrc);
		LB_ASSERT(result != 0, "strcpy_s Fail!");

		return (result == 0);
	}

	inline bool StrConcat(char* pDest, Size pDestSize, const char* pSrc)
	{
		int result = ::strcat_s(pDest, static_cast<rsize_t>(pDestSize), pSrc);
		LB_ASSERT(result != 0, "strcat_s Fail!");

		return (result == 0);
	}

	inline bool StrConcat(wchar_t* pDest, Size pDestSize, const wchar_t* pSrc)
	{
		int result = ::wcscat_s(pDest, static_cast<rsize_t>(pDestSize), pSrc);
		LB_ASSERT(result != 0, "strcat_s Fail!");

		return (result == 0);
	}

	template<Size TSize>
	inline bool StrConcat(char (&pDest)[TSize], const char* pSrc)
	{
		int result = ::strcat_s(pDest, pSrc);
		LB_ASSERT(result != 0, "strcpy_s Fail!");

		return (result == 0);
	}

	template<Size TSize>
	inline bool StrConcat(wchar_t (&pDest)[TSize], const wchar_t* pSrc)
	{
		int result = ::wcscat_s(pDest, pSrc);
		LB_ASSERT(result != 0, "strcpy_s Fail!");

		return (result == 0);
	}
}
