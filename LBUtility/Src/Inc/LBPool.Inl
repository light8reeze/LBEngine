namespace LBNet
{
	template<class TObject>
	CObjectPool<TObject>::CObjectPool(Size pSize) : __mIsAlloc(false), __mObjectList(),
		__mObjectQueue(), __mUseSize(0), __mPoolSize(pSize), __mLocker()
	{
		__mObjectList.reserve(pSize);
	}

	template<class TObject>
	CObjectPool<TObject>::~CObjectPool()
	{
		Close();
	}

	template<class TObject>
	void CObjectPool<TObject>::Initialize()
	{
		LB_ASSERT(__mIsAlloc == false, "Alloc Twice!!");

		std::unique_lock<CLocker> aLocker(__mLocker);

		for (int index = 0; index < __mPoolSize; ++index)
		{
			try
			{
				TObject* aObject = new TObject;
				__mObjectList[index] = aObject;
				__mObjectQueue.push(aObject);
			}
			catch (std::exception& pException)
			{
				LB_ASSERT(0, "Bad Alloc!!");
			}
		}

		__mUseSize = 0;
		__mIsAlloc = true;
	}

	template<class TObject>
	void CObjectPool<TObject>::Close()
	{
		LB_ASSERT(__mIsAlloc == false && __mUseSize > 0, "Invalid!");

		std::unique_lock<CLocker> aLocker(__mLocker);

		if (__mIsAlloc == false)
			return;

		while (__mObjectQueue.empty() == false)
		{
			__mObjectQueue.pop();
		}

		for (auto& aObject : __mObjectList)
			SafeDelete(aObject);

		__mIsAlloc = false;
		__mUseSize = 0;
	}

	template<class TObject>
	TObject* CObjectPool<TObject>::NewObject()
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

	template<class TObject>
	bool CObjectPool<TObject>::DeleteObject(TObject*& pObject)
	{
		LB_ASSERT(__mIsAlloc == true,	"Call Initialize First!");
		LB_ASSERT(pObject != nullptr,	"Delete NullPtr!!");
		
		if (__mUseSize >= GetMaxSize())
			return false;

		bool aCheckFlag = false;
		for (auto& aPtr : __mObjectList)
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

	template<class TObject>
	constexpr Size CObjectPool<TObject>::GetMaxSize()
	{
		return __mPoolSize;
	}

	template<class TObject>
	Size CObjectPool<TObject>::GetUseSize()
	{
		return __mUseSize;
	}
}