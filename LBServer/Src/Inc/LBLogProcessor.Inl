namespace LBNet
{
	template<typename TLogSystem>
	void CLogProcessor::AddLogSystem(LogOutputNo&& pOutput)
	{
		static_assert(std::is_base_of<ILogSystem, TLogSystem>::value);

		if (__mLogSystemList.find(pOutput) != __mLogSystemList.end())
			return;

		__mLogSystemList.emplace(std::move(pOutput), std::make_unique<TLogSystem>());
	}
}