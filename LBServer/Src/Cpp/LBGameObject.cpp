#include "LBGameObject.h"

namespace LBNet
{
	CGameObject::CGameObject() : _mSession()
	{
	}

	void CGameObject::LinkSession(SharedObject<CSession>& pSession)
	{
		_mSession = std::move(WeakObject<CSession>(pSession));
	}

	void CGameObject::Unlink()
	{
		_mSession = std::move(WeakObject<CSession>());
	}
}