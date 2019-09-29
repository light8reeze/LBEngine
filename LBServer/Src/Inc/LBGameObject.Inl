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
}