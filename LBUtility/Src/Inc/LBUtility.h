/**
	@file	LBUtility.h
	@brief	LBUtility�� ����ϱ� ���� �ʿ��� ���� �������
	@date	2019-02-17
	@auther Light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include <crtdbg.h>
#include <assert.h>

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
#define NOMINMAX

#ifdef _WINDOWS
//TODO : OS �������� �ڵ屸���� ���� ���ߴܰ迡�� �������� �ʴ´�.
/////////////////////////////////////////////////////////////////////////
// SDKDDKVer.h�� �����ϸ� �ְ� ������ ���뼺�� ���� Windows �÷����� ���ǵ˴ϴ�.
// ���� Windows �÷����� ���� ���� ���α׷��� �����Ϸ��� ��쿡�� SDKDDKVer.h�� �����ϱ� ����
// WinSDKVer.h�� �����ϰ� _WIN32_WINNT ��ũ�θ� �����Ϸ��� �÷������� �����Ͻʽÿ�.
//#include <SDKDDKVer.h>
/////////////////////////////////////////////////////////////////////////
#endif //_WINDOWS

#include <stdexcept>
#include <type_traits>

/**
	@brief std::rel_ops ��� ���� <, == �����ڸ� ���������� >, != �����ڰ� �ڵ� ���ǵȴ�.
*/
#include <utility>
using namespace std::rel_ops;

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
#define LB_UTILL_EXPORT	__declspec(dllimport)
#else
#define LB_UTILL_EXPORT	__declspec(dllexport)
#endif //LOAD_LBUTILL

/**
	@brief		assert ���� ��ũ��
	@param pExp ������ ǥ����
	@param pMsg	assert�߻��� ����� �޼���
*/
#define LB_ASSERT(pExp, pMsg) assert((pExp) && (pMsg))

namespace LBNet
{
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
		@param T1		���� ������ ��
		@param T2		���� ������ ��
		@warning		ȥ���� ���ϱ� ���� �� ���ڸ� ��� ������Ÿ���� �־��ش�.
						������, �Ϲ� ������ �������� ��� ���װ� �߻��� ���ɼ��� ����.
						(ex1 : T1 = int*, T2 = void*) => �����ͺ񱳰� �°� �����
						(ex2 : T1 = int*, T2 = char)  => �����ͺ񱳰� �°� ������� ����
		@return bool	�� �����Ͱ� ���� �ּ��̸� true �ƴϸ� false
	*/
	template<typename T1, typename T2>
	inline bool IsSameAddress(T1 pT1, T2 pT2)
	{
		if(std::is_same<T1, T2>::value)
			return (pT1 == pT2);

		return (pT1 == reinterpret_cast<T1>(pT2));
	}

	/**
		@brief	LBNet���� ����ϴ� ũ�� Ÿ�� ����
	*/
	using Size = unsigned int;

	/**
		@brief	LBNet���� ����ϴ� �⺻ �ð� ���� ����
	*/
	using Tick = std::chrono::milliseconds;
}