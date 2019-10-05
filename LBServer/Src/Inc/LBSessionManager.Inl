namespace LBNet
{
	template<typename TObject>
	SharedObject<TObject> CSessionManager::GetGameObject(CSessionKey& pKey)
	{
		auto aSession = __mSessionList[pKey.mField.mIndex];

		LB_ASSERT(aSession->GetSessionKey().mField.mIndex == pKey.mField.mIndex, "Wrong Index");

		if (aSession->GetState() == CManagedObject::EState::eUsing)
		{
			auto aSessionKey = aSession->GetSessionKey();
			
			if (pKey == aSessionKey && aSessionKey.mField.mIsSet == 1)
			{
				auto aGameObject = aSession->GetGameObject<TObject>();
				return aGameObject;
			}
		}

		return nullptr;
	}

	template<typename TObject>
	void CSessionManager::AddShard(unsigned short pSvrNo, const char* pIp, unsigned short pPort)
	{
		static_assert(std::is_base_of<CShardObject, TObject>::value == true);

		CSessionKey aKey;
		aKey.mField.mIndex = static_cast<unsigned int>(__mShardList.size());
		aKey.mField.mType = 1;
		auto aShard(std::make_shared<CShard<TObject>>());
		auto aShardObject(std::make_shared<TObject>());

		aShard->SetSessionKey(aKey);
		aShard->SetAddress(pIp, pPort);
		aShard->SetServerNo(pSvrNo);
		aShard->SetGameObject<TObject>(aShardObject);

		auto aSessionPtr = std::static_pointer_cast<CSession>(aShard);
		aShardObject->LinkSession(aSessionPtr);
		__mShardList.emplace_back(aSessionPtr);

		LB_ASSERT(aKey.mField.mIndex == __mShardList.size() - 1, "Error!");
	}
}