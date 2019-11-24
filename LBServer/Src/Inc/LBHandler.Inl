namespace LBNet
{
	template<typename THandler>
	typename CMessageHandler<THandler>::HandlerList CMessageHandler<THandler>::__mHandlerList;

	template<typename THandler>
	ErrCode CMessageHandler<THandler>::Register(MessageNumber pNumber, THandler&& pHandler)
	{
		static_assert(std::is_function(THandler));

		auto aResult = __mHandlerList.emplace(pNumber, pHandler);
		if (aResult.second == false)
			return eErrCodeAlreadyRegistered;

		return 0;
	}

	template<typename THandler>
	template<typename... TArgs>
	ErrCode CMessageHandler<THandler>::Process(MessageNumber pNumber, TArgs... pArgs)
	{
		auto aIter = __mHandlerList.find(pNumber);
		if (aIter == __mHandlerList.end())
			return eErrCodeInvalidMessage;

		auto aResult = aIter->second(pArgs...);
		return aResult;
	}
}