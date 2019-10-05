#include "LBSessionManager.h"
#include "LBFactory.h"

namespace LBNet
{
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

		WriteLock aWriteLock(__mMutex);
		for (auto& aSession : __mSessionList)
		{
			aSession->Close();
		}

		__mSessionList.clear();
	}

	SharedObject<CSession> CSessionManager::GetShard(CSessionKey& pKey)
	{
		auto aSession = __mShardList[pKey.mField.mIndex];
		LB_ASSERT(aSession->GetSessionKey().mField.mIndex == pKey.mField.mIndex, "Wrong Index");

		if (aSession->GetSessionKey() == pKey)
		{
			return aSession;
		}

		return nullptr;
	}

	void CSessionManager::InitShard()
	{
		for (auto& aShard : __mShardList)
		{
			aShard->Initialize();
		}
	}

	CSessionKey CSessionManager::GetKey()
	{
		WriteLock aLock(__mMutex);

		if (__mWaitQueue.empty())
			return CSessionKey();

		CSessionKey aKey = __mWaitQueue.front();
		__mWaitQueue.pop();
		return aKey;
	}

	void CSessionManager::ReturnKey(CSessionKey& aKey)
	{
		WriteLock aLock(__mMutex);
		__mWaitQueue.push(aKey);
	}
}