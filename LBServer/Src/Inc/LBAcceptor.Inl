namespace LBNet
{
	template<typename THandler>
	void CAcceptor::AcceptAsync(CTCPSocket& pSocket, THandler&& pHandler)
	{
		LB_ASSERT(__mAcceptor.is_open(), "Acceptor not Open");

		__mAcceptor.async_accept(pSocket.GetSocket(), pHandler);
	}
}