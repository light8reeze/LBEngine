namespace LBNet
{
	template<typename TObject>
	SharedObject<CSender> CSender::Allocate()
	{
		return CSender::Allocate(sizeof(TObject));
	}

	template<typename TObject>
	TObject* CSender::GetWritePointer()
	{
		auto aPtr = reinterpret_cast<char*>(__mChunk);
		return reinterpret_cast<TObject*>(aPtr + sizeof(SendHeader) + GetEncryptHdSize());
	}

	template<typename TObject>
	void CSender::SetData(TObject& pObject)
	{
		LB_ASSERT(sizeof(TObject) <= __mChunkCount * eSzSendChunk - GetEncryptHdSize(), "Error");
		auto aPtr = reinterpret_cast<char*>(__mChunk);
		auto aDataPtr = reinterpret_cast<TObject*>(aPtr + sizeof(SendHeader) + GetEncryptHdSize());

		(*aDataPtr) = pObject;
	}
}