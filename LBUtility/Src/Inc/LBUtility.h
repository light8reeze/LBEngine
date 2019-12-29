/**
	@file	LBUtility.h
	@brief	LBUtility�� ����ϱ� ���� �ʿ��� ���� �������
	@date	2019-02-17
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include <assert.h>

//#define DEVELOP_MODE

#ifdef WIN32
	#define X86
#endif //WIN32

/**
	@brief		������ OS�� ��ũ��, ���� ������ ���� OS�� �������� �ڵ�� ���� ��ũ�η� ��ó���Ѵ�.
	@warning	_WINDOWS, _LINUX �Ѵ� ���ǽ� ������ ������ �߻��Ѵ�
*/
#define _WINDOWS
//#define _LINUX
#if defined (_WINDOWS) && (_LINUX)
	#error define OS _WINDOWS or _LINUX only
#endif //(_WINDOWS) && (_LINUX)

/**
	@brief windows�� min, max�� ������� �ʰ� std�� min, max�� ����Ѵ�.
*/
#ifndef NOMINMAX
	#define NOMINMAX
#endif

#ifdef _WINDOWS
/////////////////////////////////////////////////////////////////////////
// SDKDDKVer.h�� �����ϸ� �ְ� ������ ���뼺�� ���� Windows �÷����� ���ǵ˴ϴ�.
// ���� Windows �÷����� ���� ���� ���α׷��� �����Ϸ��� ��쿡�� SDKDDKVer.h�� �����ϱ� ����
// WinSDKVer.h�� �����ϰ� _WIN32_WINNT ��ũ�θ� �����Ϸ��� �÷������� �����Ͻʽÿ�.
#include <SDKDDKVer.h>
/////////////////////////////////////////////////////////////////////////
#endif //_WINDOWS

#include <stdexcept>
#include <type_traits>

/**
	@brief std::chrono_literals ��� ����
*/
#include <chrono>
using namespace std::chrono_literals;

/**
	@brief		DllExport ���� ��ũ��
	@details	dll�� �޾� ���ø����̼��� ������ ������ LBUtillity.h�� �����ϱ� ���� LOAD_LBUTILL��ũ�θ� �����Ѵ�.
*/
#ifdef LOAD_LBUTILL
	#define LBU_EXPORT						__declspec(dllimport)
	#define LBU_EXPORT_TEMPLATE(pClass)		extern template class LBU_EXPORT pClass
#else
	#define LBU_EXPORT						__declspec(dllexport)
	#define LBU_EXPORT_TEMPLATE(pClass)		template class LBU_EXPORT pClass
#endif //LOAD_LBUTILL

/**
	@brief		assert ���� ��ũ��
	@param pExp ������ ǥ����
	@param pMsg	assert�߻��� ����� �޼���
*/
#define LB_ASSERT(pExp, pMsg) assert((pExp) && (pMsg))

/**
	@brief		����� ��忡�� ���� �ڵ� ��ũ�� (Release��忡�� ����)
	@param pExp ����׿� ����� �ڵ�
*/
#ifdef _DEBUG
	#define DEBUG_CODE(pExp) pExp
#else
	#define DEBUG_CODE(pExp)
#endif //_DEBUG

namespace LBNet
{
	/**
		@brief	LBEngine���� ����ϴ� ũ�� Ÿ�� ����
	*/
	using Size = unsigned short;

	/**
		@brief	LBEngine���� ����ϴ� �⺻ �ð� ���� ����
	*/
	using Tick		= std::chrono::duration<unsigned long long, std::milli>;
	using TickCount	= Tick::rep;

	/**
		@brief			Enum�� Ÿ���� ������ ��ȯ���ִ� �Լ�
		@param TEnum	��ȯ�� Enum��
		@return auto	��ȯ�� Enum��
	*/
	template<typename TEnum>
	constexpr auto UnderLying(TEnum e) -> typename std::underlying_type<TEnum>::type
	{
		return static_cast<typename std::underlying_type<TEnum>::type>(e);
	}

	/**
		@brief			�� �����Ͱ� ���� �ּ����� �˻��ϴ� �Լ�
		@param T1		���� ������ Ÿ��
		@param T2		���� ������ Ÿ��
		@warning		ȥ���� ���ϱ� ���� �� ���ڸ� ��� ������Ÿ���� �־��ش�.
						1. ������, �Ϲ� ������ �������� ��� ���װ� �߻��� ���ɼ��� ����.
						(ex1 : T1 = int*, T2 = void*) => �����ͺ񱳰� �°� �����
						(ex2 : T1 = int*, T2 = char)  => �����ͺ񱳰� �°� ������� ����
						2. const �������� ��� const�� �����Ͽ� ���ڷ� �־�� �Ѵ�.
		@return bool	�� �����Ͱ� ���� �ּ��̸� true �ƴϸ� false
	*/
	template<typename T1, typename T2>
	inline bool IsSameAddress(T1 pT1, T2 pT2)
	{
		static_assert(std::is_pointer<T1>::value && std::is_pointer<T2>::value);
		using Non_cvT1 = std::remove_cv_t<T1>;
		using Non_cvT2 = std::remove_cv_t<T2>;

		return (reinterpret_cast<void*>(const_cast<Non_cvT1>(pT1))
			== reinterpret_cast<void*>(const_cast<Non_cvT2>(pT2)));
	}

	/**
		@brief			LBUtillity�� ������ �޴� �Լ�
		@return Version	LBUtillity�� ����
	*/
	using Version = unsigned int;
	constexpr Version LBU_EXPORT GetLBUVersion();
	
	/**
		@brief			Ư�� �����͸� �Ҵ� �����ϴ� �Լ�
		@param TType	������ ������ �ڷ���
		@param TType&	������ ������
		@warning		TType�� �ݵ�� �����Ϳ��� �Ѵ�.
	*/
	template<typename TType>
	inline void SafeDelete(TType& pObject)
	{
		static_assert(std::is_pointer<TType>::value);

		if (pObject)
		{
			delete pObject;
			pObject = nullptr;
		}
	}
	
	/**
		@brief			Ư�� �����͸� �Ҵ� �����ϴ� �Լ�(�迭)
		@param TType	������ ������ �ڷ���
		@param TType&	������ ������
		@warning		TType�� �ݵ�� �����Ϳ��� �Ѵ�.
	*/
	template<typename TType>
	inline void SafeArrayDelete(TType& pObject)
	{
		static_assert(std::is_pointer<TType>::value);

		if (pObject)
		{
			delete[] pObject;
			pObject = nullptr;
		}
	}
	
	/**
		@brief �����ڵ� Ÿ��
	*/
	using ErrCode = std::size_t;
}

/**
	@brief		�����ڵ� ��� ��ũ��
	@comment	pErr�� ����� �������� �ִ´�.
*/
#define LB_ERRCODE(pErr) const LBNet::ErrCode pErr = std::hash<std::string>{}(#pErr)