namespace LBNet
{
	template<typename TObject>
	void CSession::SetObject(SharedObject<TObject>& pObject)
	{
		LB_ASSERT(__mGameObject.get()	== nullptr, "Error!");
		LB_ASSERT(pObject.get()			!= nullptr, "Error!");

		__mGameObject = std::static_pointer_cast<SharedObject<CGameObject>>(pObject);
		__mGameObject->LinkSession(this);
	}

	template<typename TObject>
	SharedObject<TObject> CSession::GetGameObject()
	{
		return std::dynamic_pointer_cast<SharedObject<TObject>>(__mGameObject);
	}

	template<>
	SharedObject<CGameObject> CSession::GetGameObject()
	{
		return __mGameObject;
	}
}