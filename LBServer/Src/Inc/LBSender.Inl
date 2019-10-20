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
		return reinterpret_cast<TObject*>(aPtr + sizeof(SendHeader));
	}
}