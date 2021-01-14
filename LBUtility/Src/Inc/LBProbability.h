/**
	@file	LBProbability.h
	@brief	LBUtillity의 확률 계산 관련 헤더
	@date	2019-07-28
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBUtility.h"
#include "LBRandom.h"
#include <type_traits>

namespace LBNet
{
	/**
		@brief		확률 계산 클래스
		@date		2019-07-28
		@auther		light8reeze(light8reeze@gmail.com)
	*/
	class CProbability
	{
	public:
		template<typename TType>
		static bool IsSuccess(TType pPercent);

		template<typename TVector>
		static int GetChoice(const TVector& pVector);

		template<typename TType, std::size_t TSize>
		static int GetChoice(TType (&pArray)[TSize]);

	private:
		template<typename TType>
		static bool __IsSuccessImpl(TType pPercent, std::true_type);
		template<typename TType>
		static bool __IsSuccessImpl(TType pPercent, std::false_type);
	};
}

#include "LBProbability.Inl"
