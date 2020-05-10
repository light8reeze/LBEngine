namespace LBNet
{
	template<typename TObject>
	void CSession::SetGameObject(SharedObject<TObject>& pObject)
	{
		static_assert(std::is_base_of<CGameObject, TObject>::value == true);

		LB_ASSERT(__mGameObject.get()	== nullptr, "Error!");
		LB_ASSERT(pObject.get()			!= nullptr, "Error!");

		__mGameObject = std::static_pointer_cast<CGameObject>(pObject);
	}

	template<typename TObject>
	SharedObject<TObject> CSession::GetGameObject()
	{
		static_assert(std::is_base_of<CGameObject, TObject>::value == true);

		return __GetGameObjectImpl<TObject>(std::is_same<CGameObject, TObject>());
	}

	template<typename TObject>
	SharedObject<TObject> CSession::__GetGameObjectImpl(std::true_type)
	{
		return __mGameObject;
	}

	template<typename TObject>
	SharedObject<TObject> CSession::__GetGameObjectImpl(std::false_type)
	{
		SharedObject<TObject> aPtr = SharedCast<CGameObject, TObject>(__mGameObject);
		return std::move(aPtr);
	}
}