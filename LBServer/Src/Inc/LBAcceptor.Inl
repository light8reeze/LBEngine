namespace LBNet
{
	template<typename THandler>
	void CAcceptor::AcceptAsync(CSession& pSession, THandler&& pHandler)
	{
		LB_ASSERT(__mAcceptor.is_open(), "Acceptor not Open");

		__mAcceptor.async_accept(pSession.__mSocket.GetSocket(), CIOContext::Instance().BindExecuter(pHandler));
	}
}