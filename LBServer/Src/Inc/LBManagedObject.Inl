namespace LBNet
{
	template<typename TObject>
	CManagedObject::ManagedPtr<TObject> CManagedObject::MakeManaged(TObject& pObject)
	{
		CManagedObject::ManagedPtr<TObject> aManaged(&pObject
			,[](TObject* pObject)
		{
			pObject->OnDelete();
		});
		
		return aManaged;
	}
}