#include "LBGameObject.h"

namespace LBNet
{
	CGameObject::CGameObject() : _mSession()
	{
	}

	void CGameObject::LinkSession(CSession& pSession)
	{
		LB_ASSERT(_mSession == nullptr, "Error");

		_mSession = std::move(_SessionPtr(&pSession));
	}

	void CGameObject::Unlink()
	{
		LB_ASSERT(_mSession != nullptr, "Error");

		_mSession = nullptr;
	}
}