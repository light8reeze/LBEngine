namespace LBNet
{
	template<typename THandler>
	auto CIOContext::BindExecuter(THandler&& pHandler)
	{
		return asio::bind_executor(__mStrand, pHandler);
	}

	template<typename THandler>
	void CIOContext::Post(THandler&& pHandler)
	{
		return __mIOContext.post(__mStrand, pHandler);
	}
}