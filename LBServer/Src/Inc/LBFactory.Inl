namespace LBNet
{
#pragma region CObjectPoolEx
	template<typename TObject>
	CObjectPoolEx<TObject>::CObjectPoolEx(int pSize) : IObjectPool(), CObjectPoolEx<TObject>(pSize)
	{
	}

	template<typename TObject>
	CObjectPoolEx<TObject>::~CObjectPoolEx()
	{
	}

	template<typename TObject>
	void CObjectPoolEx<TObject>::Initialize()
	{
		CObjectPool<TObject>::Initialize();
	}

	template<typename TObject>
	void CObjectPoolEx<TObject>::Close()
	{
		CObjectPool<TObject>::Close();
	}
#pragma endregion 

#pragma region CFactory
	CFactory::CFactory() : __mPools(), __mIsInitial(false)
	{
	}

	CFactory::~CFactory()
	{
		Close();
	}

	CFactory& CFactory::Instance()
	{
		return __mSingleton;
	}

	ErrCode CFactory::Initialize()
	{
		LB_ASSERT(__mIsInitial == false, "Error");

		for (auto& aPair : __mPools)
		{
			aPair.second->Initialize();
		}

		__mIsInitial = true;
		return 0;
	}

	ErrCode CFactory::Close()
	{
		LB_ASSERT(__mIsInitial == true, "Error");

		__mPools.clear();

		return 0;
	}

	template<typename TObject>
	bool CFactory::AddObjectPool(int pSize)
	{
		using ObjectPool = CObjectPoolEx<TObject>;
		std::size_t aKey = typeid(TObject).hash_code();

		if (__mPools.find(aKey) == __mPools.end())
			return false;

		__PoolPtr aPool = std::make_unique<ObjectPool>(pSize);
		auto aResult = __mPools.insert(std::make_pair<std::size_t, __PoolPtr>(aKey, aPool));

		LB_ASSERT(aResult.second == true, "Error!");
		return true;
	}

	template<typename TObject, typename TDeleter>
	SharedObject<TObject> CFactory::New(TDeleter&& pDeleter)
	{
		using ObjectPool = CObjectPoolEx<TObject>;

		std::size_t aKey = typeid(TObject).hash_code();

		if (__mPools.find(aKey) == __mPools.end())
			return nullptr;

		auto		aIter		= __mPools.find(aKey);
		__PoolPtr&	aPool		= aIter->second;
		ObjectPool* aObjPool	= dynamic_cast<ObjectPool>(aPool.get());

		LB_ASSERT(aObjPool != nullptr, "Exception!");

		TObject* aObject = aObjPool->NewObject();
		return MakePtr(aObject, pDeleter);
	}

	template<typename TObject>
	bool CFactory::Delete(TObject*& pObject)
	{
		using ObjectPool = CObjectPoolEx<TObject>;

		std::size_t aKey = typeid(TObject).hash_code();

		if (__mPools.find(aKey) == __mPools.end())
			return false;

		auto		aIter		= __mPools.find(aKey);
		__PoolPtr&	aPool		= aIter->second;
		ObjectPool* aObjPool	= dynamic_cast<ObjectPool>(aPool.get());

		LB_ASSERT(aObjPool != nullptr, "Exception!");

		return aObjPool->DeleteObject(pObject);
	}

	template<typename TObject, typename TDeleter>
	SharedObject<TObject> CFactory::MakePtr(TObject*& pObject, TDeleter&& pDeleter)
	{
		return std::make_shared<TObject>(pObject, pDeleter);
	}
#pragma endregion 
}