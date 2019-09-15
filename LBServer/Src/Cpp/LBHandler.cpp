#include "LBHandler.h"

namespace LBNet
{
	ErrCode CMessageHandler::Register(MessageNumber pNumber, HandlerType&& pHandler)
	{
		auto aResult = __mHandlerList.emplace(pNumber, pHandler);
		if (aResult.second == false)
			return 1;

		return 0;
	}

	ErrCode CMessageHandler::Process(MessageNumber pNumber, CPacketHeader* pData, int pDataSize, CSession& pSession, SharedObject<CGameObject>& pObject)
	{
		auto aIter = __mHandlerList.find(pNumber);
		if (aIter == __mHandlerList.end())
			return 1;

		auto aResult = aIter->second(pData, pDataSize, pSession, pObject);
		return aResult;
	}
}