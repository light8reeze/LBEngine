/**
	@file	LBRandom.h
	@brief	LBUtillity�� ���� �߻� ���� ���
	@date	2019-07-28
	@auther Light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBUtility.h"
#include <random>

namespace LBNet
{
#ifdef X86
	using MTEngine = std::mt19937;
#elif X64
	using MTEngine = std::mt19937_64;
#endif //X86

	/**
		@brief		���� Ŭ����
		@comment	C++11�� �޸��� Ʈ������ ������ ����Ͽ� ����
		@date		2019-07-28
		@auther		Light8reeze(light8reeze@gmail.com)
	*/
	class CRandom
	{
	public:
		template<typename TType>
		static TType	GetRandom(TType pMin = std::numeric_limits<TType>::min(), TType pMax = std::numeric_limits<TType>::max());

	private:
		template<typename TType>
		static TType	__GetRandomImpl(TType pMin, TType pMax, std::true_type);
		template<typename TType>
		static TType	__GetRandomImpl(TType pMin, TType pMax, std::false_type);
	};
}

#include "LBRandom.Inl"