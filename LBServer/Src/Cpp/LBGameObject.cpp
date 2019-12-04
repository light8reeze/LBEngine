#include "LBGameObject.h"

namespace LBNet
{
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

	ErrCode CGameObject::Send(SharedObject<CSender>& pSender)
	{
		if (!_mSession.expired())
		{
			auto aShared = _mSession.lock();
			return aShared->Send(pSender);
		}

		return 0;
	}

	void CGameObject::SetDisconnect()
	{
		if (!_mSession.expired())
		{
			auto aShared = _mSession.lock();
			aShared->SetDisconnect();
		}
	}

	std::string&& CGameObject::GetIPAddress() const
	{
		if (!_mSession.expired())
		{
			auto aShared = _mSession.lock();
			return std::move(aShared->GetEndPoint().address().to_string());
		}

		return std::move(std::string(""));
	}

	unsigned short CGameObject::GetPort() const
	{
		if (!_mSession.expired())
		{
			auto aShared = _mSession.lock();
			return aShared->GetEndPoint().port();
		}

		return 0;
	}
}