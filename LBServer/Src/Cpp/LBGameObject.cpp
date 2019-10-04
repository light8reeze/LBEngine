#include "LBGameObject.h"
#include "LBFactory.h"

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
			aShared->Close();
		}
	}
#pragma endregion CGameObject

#pragma region CSessionManager
	CSessionManager CSessionManager::__mSingleton;

	CSessionManager& CSessionManager::Instance()
	{
		return __mSingleton;
	}

	void CSessionManager::Initialize(int pMaxSession)
	{
		LB_ASSERT(__mMutex.GetOwner() == std::thread::id(), "Must Exec SingleThread Only!");
		
		__mSessionList.reserve(pMaxSession);

		for (int index = 0; index < pMaxSession; ++index)
		{
			CSessionKey aKey;
			aKey.mField.mIndex = index;
			auto aSession = CFactory::Instance().New<CSession>();
			aSession->SetSessionKey(aKey);

			LB_ASSERT(index == __mSessionList.size(), "Error!");
			__mSessionList.emplace_back(std::move(aSession));
			__mWaitQueue.emplace(std::move(aKey));
		}
	}

	SharedObject<CSession> CSessionManager::GetSession(CSessionKey& pKey)
	{
		auto aSession = __mSessionList[pKey.mField.mIndex];
		LB_ASSERT(aSession->GetSessionKey().mField.mIndex == pKey.mField.mIndex, "Wrong Index");

		if (aSession->GetSessionKey() == pKey)
		{
			return aSession;
		}

		return nullptr;
	}

	void CSessionManager::Close()
	{
		LB_ASSERT(__mMutex.GetOwner() == std::thread::id(), "Must Exec SingleThread Only!");

		TWriteLock aWriteLock(__mMutex);
		for (auto& aSession : __mSessionList)
		{
			aSession->Close();
		}

		__mSessionList.clear();
	}

	CSessionKey CSessionManager::GetKey()
	{
		TWriteLock aLock(__mMutex);

		if (__mWaitQueue.empty())
			return CSessionKey();

		CSessionKey aKey = __mWaitQueue.front();
		__mWaitQueue.pop();
		return aKey;
	}

	void CSessionManager::ReturnKey(CSessionKey& aKey)
	{
		TWriteLock aLock(__mMutex);
		__mWaitQueue.push(aKey);
	}
#pragma endregion CSessionManager
}