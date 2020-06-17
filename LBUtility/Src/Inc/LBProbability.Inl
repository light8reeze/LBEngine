namespace LBNet
{
	template<typename TType>
	static bool CProbability::IsSuccess(TType pPercent)
	{
		return __IsSuccessImpl(pPercent, std::is_integral<std::remove_reference_t<TType>>());
	}

	template<typename TVector>
	static int CProbability::GetChoice(const TVector& pVector)
	{
		using ProbValue = typename TVector::value_type;
		ProbValue	aRandom = CRandom::GetRandom(ProbValue(0), ProbValue(100));
		ProbValue	aSum = static_cast<ProbValue>(0);
		int			aResult = 0;
		
		for(const auto& aIter : pVector)
		{
			ProbValue& aNowProb = (*aIter);

			if (aRandom < aNowProb + aSum)
			{
				break;
			}

			++aResult;
			aSum += aNowProb;
		}

		return aResult;
	}

	template<typename TType, std::size_t TSize>
	static int CProbability::GetChoice(TType (&pArray)[TSize])
	{
		TType	aRandom	= CRandom::GetRandom(TType(0), TType(100));
		TType	aSum	= static_cast<TType>(0);
		int		aResult = 0;

		for (const auto& aProb : pArray)
		{
			if (aRandom < aProb + aSum)
			{
				break;
			}

			++aResult;
			aSum += aProb;
		}

		return aResult;
	}

	template<typename TType>
	static bool CProbability::__IsSuccessImpl(TType pPercent, std::true_type)
	{
		TType aRandom = CRandom::GetRandom(TType(0), TType(100));
		return (aRandom < pPercent) ? true : false;
	}

	template<typename TType>
	static bool CProbability::__IsSuccessImpl(TType pPercent, std::false_type)
	{
		TType aRandom = CRandom::GetRandom(TType(0.0), TType(100.0));
		return (aRandom < pPercent) ? true : false;
	}
}