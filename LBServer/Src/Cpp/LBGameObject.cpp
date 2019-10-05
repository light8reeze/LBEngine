#include "LBGameObject.h"

namespace LBNet
{
#pragma region CGameObject
	CGameObject::CGameObject() : _mSession()
	{
	}

	void CGameObject::LinkSession(SharedObject<CSession>& pSession)
	{
		_mSession = pSession;
	}

	void CGameObject::Unlink()
	{
		_mSession = std::move(WeakObject<CSession>());
	}

	ErrCode CGameObject::Send(void* pBuffer, int pSize)
	{
		if (!_mSession.expired())
		{
			auto aShared = _mSession.lock();
			return aShared->Send(pBuffer, pSize);
		}

		return 0;
	}

	const CSessionKey CGameObject::GetSessionKey() const
	{
		if (!_mSession.expired())
		{
			auto aShared = _mSession.lock();
			return aShared->GetSessionKey();
		}

		return CSessionKey();
	}

	void CGameObject::SetDisconnect()
	{
		if (!_mSession.expired())
		{
			auto aShared = _mSession.lock();
			aShared->SetDisconnect();
		}
	}
#pragma endregion CGameObject
}