#include <iostream>
namespace LBNet
{
#pragma region CObjectPoolEx
	template<typename TObject>
	CObjectPoolEx<TObject>::CObjectPoolEx(int pSize) : IObjectPool(), CObjectPool<TObject>(pSize)
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

	template<typename TObject>
	bool CFactory::AddObjectPool(int pSize)
	{
		using ObjectPool = CObjectPoolEx<TObject>;
		std::size_t aKey = typeid(TObject).hash_code();

		if (__mPools.find(aKey) != __mPools.end())
			return false;

		__PoolPtr aPool = std::make_unique<ObjectPool>(pSize);
		auto aResult = __mPools.emplace(aKey, std::move(aPool));

		LB_ASSERT(aResult.second == true, "Error!");
		return true;
	}

	template<typename TObject>
	SharedObject<TObject> CFactory::New()
	{
		return New<TObject>([](TObject* pObject)
		{
			if (pObject == nullptr)
				return false;

			return CFactory::Instance().Delete(pObject);
		});
	}

	template<typename TObject, typename TDeleter>
	SharedObject<TObject> CFactory::New(TDeleter&& pDeleter)
	{
		TObject* aObject = Allocate<TObject>();
		return MakePtr(aObject, pDeleter);
	}

	template<typename TObject>
	TObject* CFactory::Allocate()
	{
		using ObjectPool = CObjectPoolEx<TObject>;

		std::size_t aKey = typeid(TObject).hash_code();

		if (__mPools.find(aKey) == __mPools.end())
			return nullptr;

		auto		aIter = __mPools.find(aKey);
		__PoolPtr&	aPool = aIter->second;
		ObjectPool* aObjPool = dynamic_cast<ObjectPool*>(aPool.get());

		LB_ASSERT(aObjPool != nullptr, "Exception!");

		TObject* aObject = aObjPool->NewObject();
		return aObject;
	}

	template<typename TObject>
	bool CFactory::Delete(TObject* pObject)
	{
		using ObjectPool = CObjectPoolEx<TObject>;
		LB_ASSERT(pObject != nullptr, "Exception!");

		std::size_t aKey = typeid(TObject).hash_code();

		if (__mPools.find(aKey) == __mPools.end())
			return false;

		auto		aIter		= __mPools.find(aKey);
		__PoolPtr&	aPool		= aIter->second;
		ObjectPool* aObjPool	= dynamic_cast<ObjectPool*>(aPool.get());

		LB_ASSERT(aObjPool != nullptr, "Exception!");

		return aObjPool->DeleteObject(pObject);
	}

	template<typename TObject, typename TDeleter>
	SharedObject<TObject> CFactory::MakePtr(TObject*& pObject, TDeleter&& pDeleter)
	{
		return SharedObject<TObject>(pObject, pDeleter);
	}
#pragma endregion 
}