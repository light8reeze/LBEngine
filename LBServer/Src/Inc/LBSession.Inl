namespace LBNet
{
	template<typename TObject>
	void CSession::SetObject(CFactory::ObjectPtr<TObject>& pObject)
	{
		LB_ASSERT(__mGameObject.get()	== nullptr, "Error!");
		LB_ASSERT(pObject.get()			!= nullptr, "Error!");

		__mGameObject = pObject;
		__mGameObject->LinkSession(*this);
	}
}