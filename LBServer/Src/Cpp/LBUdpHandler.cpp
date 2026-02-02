#include "LBUdpHandler.h"

namespace LBNet
{
	CUdpHandler CUdpHandler::__mSingleton;

	CUdpHandler& CUdpHandler::Instance()
	{
		return __mSingleton;
	}
}