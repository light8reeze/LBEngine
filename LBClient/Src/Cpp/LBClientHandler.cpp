#include "LBClientHandler.h"

namespace LBNet
{
	CClientHandler CClientHandler::__mSingleton;

	CClientHandler& CClientHandler::Instance()
	{
		return __mSingleton;
	}
}