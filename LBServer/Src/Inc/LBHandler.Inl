namespace LBNet
{
	template<typename THandler>
	ErrCode CMessageHandler<THandler>::Register(MessageNo pNumber, THandler&& pHandler)
	{
		auto aResult = __mHandlerList.emplace(pNumber, pHandler);
		if (aResult.second == false)
			return eErrCodeAlreadyRegistered;

		return 0;
	}

	template<typename THandler>
	template<typename... TArgs>
	ErrCode CMessageHandler<THandler>::Process(MessageNo pNumber, TArgs... pArgs)
	{
		auto aIter = __mHandlerList.find(pNumber);
		if (aIter == __mHandlerList.end())
			return eErrCodeInvalidMessage;

		auto aResult = aIter->second(pArgs...);
		return aResult;
	}
}