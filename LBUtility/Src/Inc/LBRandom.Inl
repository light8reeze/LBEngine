namespace LBNet
{
	template<typename TType>
	inline TType CRandom::GetRandom(TType pMin, TType pMax)
	{
		return __GetRandomImpl(pMin, pMax, std::is_integral<std::remove_reference_t<TType>>()) % pMax;
	}

	template<typename TType>
	inline TType CRandom::__GetRandomImpl(TType pMin, TType pMax, std::true_type)
	{
		std::random_device						aDevice;
		MTEngine								aMTEngine(aDevice());
		std::uniform_int_distribution<TType>	aDist(pMin, pMax);

		return aDist(aMTEngine);
	}

	template<typename TType>
	inline TType CRandom::__GetRandomImpl(TType pMin, TType pMax, std::false_type)
	{
		std::random_device						aDevice;
		MTEngine								aMTEngine(aDevice());
		std::uniform_real_distribution<TType>	aDist(pMin, pMax);

		return aDist(aMTEngine);
	}
}