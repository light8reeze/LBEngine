namespace LBNet
{
	template<class TObject, Size TCount>
	CObjectPool<TObject, TCount>::CObjectPool() : __mIsAlloc(false), __mObjectArray(),
		__mObjectQueue(), __mUseSize(0), __mLocker()
	{
	}

	template<class TObject, Size TCount>
	CObjectPool<TObject, TCount>::~CObjectPool()
	{
		Close();
	}

	template<class TObject, Size TCount>
	void CObjectPool<TObject, TCount>::Initialize()
	{
		LB_ASSERT(__mIsAlloc == false, "Alloc Twice!!");

		std::unique_lock<CLocker> aLocker(__mLocker);

		for (int index = 0; index < TCount; ++index)
		{
			try
			{
				TObject* aObject = new TObject;
				__mObjectArray[index] = aObject;
				__mObjectQueue.push(aObject);
			}
			catch (std::exception& pException)
			{
				LB_ASSERT(0, "Bad Alloc!!");
			}
		}

		__mUseSize = TCount;
		__mIsAlloc = true;
	}

	template<class TObject, Size TCount>
	void CObjectPool<TObject, TCount>::Close()
	{
		LB_ASSERT(__mIsAlloc == false && __mUseSize > 0, "Invalid!");

		std::unique_lock<CLocker> aLocker(__mLocker);

		if (__mIsAlloc == false)
			return;

		while (__mObjectQueue.empty() == false)
		{
			__mObjectQueue.pop();
		}

		for (TObject*& aObject : __mObjectArray)
			SafeDelete(aObject);

		__mIsAlloc = false;
		__mUseSize = 0;
	}

	template<class TObject, Size TCount>
	TObject* CObjectPool<TObject, TCount>::NewObject()
	{
		LB_ASSERT(__mIsAlloc == true, "Call Initialize First!");

		TObject* aObject	= nullptr;

		{
			std::unique_lock<CLocker> aLocker(__mLocker);

			if (__mUseSize >= GetMaxSize())
				return aObject;

			aObject = __mObjectQueue.front();
			__mObjectQueue.pop();
			++__mUseSize;
		}

		LB_ASSERT(aObject != nullptr, "Invalid!");

		return aObject;
	}

	template<class TObject, Size TCount>
	bool CObjectPool<TObject, TCount>::DeleteObject(TObject*& pObject)
	{
		LB_ASSERT(__mIsAlloc == true,	"Call Initialize First!");
		LB_ASSERT(pObject != nullptr,	"Delete NullPtr!!");
		
		if (__mUseSize >= GetMaxSize())
			return false;

		bool aCheckFlag = false;
		for (TObject*& aPtr : __mObjectArray)
		{
			if (aPtr == pObject)
			{
				aCheckFlag = true;
				break;
			}
		}

		if (aCheckFlag == false)
			return false;

		{
			std::unique_lock<CLocker> aLocker(__mLocker);

			__mObjectQueue.push(pObject);
			++__mUseSize;
		}

		return true;
	}

	template<class TObject, Size TCount>
	constexpr Size CObjectPool<TObject, TCount>::GetMaxSize()
	{
		return TCount;
	}

	template<class TObject, Size TCount>
	Size CObjectPool<TObject, TCount>::GetUseSize()
	{
		return __mUseSize;
	}
}