namespace LBNet
{
	template<typename TObject>
	CManagedObject::ManagedPtr<TObject> CManagedObject::MakeManaged(TObject& pObject)
	{
		return std::make_unique(pObject, this->_OnDelete());
	}
}