#include "LBHandler.h"
#include "LBGameObject.h"

namespace LBNet
{
	CMessageHandler::__TCPHandlerList CMessageHandler::__mHandlerList;
	CMessageHandler::__UDPHandlerList CMessageHandler::__mUDPHandlerList;

	ErrCode CMessageHandler::Register(MessageNumber pNumber, TCPHandleType&& pHandler)
	{
		auto aResult = __mHandlerList.emplace(pNumber, pHandler);
		if (aResult.second == false)
			return eErrCodeAlreadyRegistered;

		return 0;
	}

	ErrCode CMessageHandler::Register(MessageNumber pNumber, UDPHandleType&& pHandler)
	{
		auto aResult = __mUDPHandlerList.emplace(pNumber, pHandler);
		if (aResult.second == false)
			return eErrCodeAlreadyRegistered;

		return 0;
	}

	ErrCode CMessageHandler::Process(MessageNumber pNumber, CPacketHeader* pData, Size pDataSize, SharedObject<CGameObject>& pObject)
	{
		auto aIter = __mHandlerList.find(pNumber);
		if (aIter == __mHandlerList.end())
			return eErrCodeInvalidMessage;

		auto aResult = aIter->second(pData, pDataSize, pObject);
		return aResult;
	}

	ErrCode CMessageHandler::Process(MessageNumber pNumber, CPacketHeader* pData, Size pDataSize, CUdpObject& pObject)
	{
		auto aIter = __mUDPHandlerList.find(pNumber);
		if (aIter == __mUDPHandlerList.end())
			return eErrCodeInvalidMessage;

		auto aResult = aIter->second(pData, pDataSize, pObject);
		return aResult;
	}
}