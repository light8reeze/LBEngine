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
		auto aShared = _mSession.lock();
		if (aShared != nullptr)
		{
			return aShared->Send(pBuffer, pSize);
		}

		return 0;
	}

	ErrCode CGameObject::Send(SharedObject<CSender>& pSender)
	{
		auto aShared = _mSession.lock();
		if (aShared != nullptr)
		{
			return aShared->Send(pSender);
		}

		return 0;
	}

	void CGameObject::SetDisconnect(ErrCode pLastErr)
	{
		auto aShared = _mSession.lock();
		if (aShared != nullptr)
		{
			aShared->SetDisconnect(pLastErr);
		}
	}

	std::string&& CGameObject::GetIPAddress() const
	{
		auto aShared = _mSession.lock();
		if (aShared != nullptr)
		{
			return std::move(aShared->GetEndPoint().address().to_string());
		}

		return std::move(std::string(""));
	}

	unsigned short CGameObject::GetPort() const
	{
		auto aShared = _mSession.lock();
		if (aShared != nullptr)
		{
			return aShared->GetEndPoint().port();
		}

		return 0;
	}
}