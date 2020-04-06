#include "LBTcpHandler.h"

namespace LBNet
{
	CTcpHandler CTcpHandler::__mSingleton;

	CTcpHandler& CTcpHandler::Instance()
	{
		return __mSingleton;
	}
}