/**
	@file	LBFactory.h
	@brief	LBServer�� ���丮 ���� �������
	@date	2019-07-30
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBServer.h"
#include "LBPool.h"
#include <map>

namespace LBNet
{
	class IObjectPool
	{
	public:
		IObjectPool() = default;
		virtual ~IObjectPool() = 0;

		virtual void Initialize() = 0;
		virtual void Close() = 0;
	};

	/**
		@brief	        ������Ʈ Ǯ Ȯ�� Ŭ����
		@details		���丮���� ������ ���� CObjectPoolŬ������ Ȯ���Ѵ�.	
		@date	        2019-08-03
		@auther         light8reeze(light8reeze@gmail.com)
	*/
	template<typename TObject>
	class CObjectPoolEx : public IObjectPool, public CObjectPool<TObject>
	{
	public:
		CObjectPoolEx(int pSize);
		virtual ~CObjectPoolEx() override;

		virtual void Initialize() override;
		virtual void Close() override;
	};

    /**
        @brief	        ������Ʈ ���丮
        @date	        2019-08-02
		@warning		1. ������Ʈ�� ���� �� �ʱ�ȭ�� caller�� ���� �Ѵ�.
						2. �⺻������ ������Ʈ �ݳ��� ����Ʈ �����Ϳ� ���� �ڵ����� �ݳ��Ѵ�.
        @auther         light8reeze(light8reeze@gmail.com)
    */
	class LBS_EXPORT CFactory
	{
	private:
		using __PoolPtr			= std::unique_ptr<IObjectPool>;
		using __PoolContainer	= std::map<std::size_t, __PoolPtr>; //Key : typeid.hashcode(), value : ObjectPool Ptr

	public:
		CFactory();
		~CFactory();

		CFactory(const CFactory&) = delete;
		CFactory(const CFactory&&) = delete;
		CFactory& operator=(const CFactory&) = delete;
		CFactory& operator=(const CFactory&&) = delete;

		static CFactory& Instance();

		ErrCode Initialize();
		ErrCode Close();

		template<typename TObject>
		bool AddObjectPool(int pSize);

		template<typename TObject>
		SharedObject<TObject> New();
		template<typename TObject, typename TDeleter>
		SharedObject<TObject> New(TDeleter&& pDeleter);

		template<typename TObject, typename TDeleter>
		static SharedObject<TObject> MakePtr(TObject*& pObject, TDeleter&& pDeleter);

		template<typename TObject>
		bool Delete(TObject* pObject);

	private:
		static CFactory __mSingleton;
		__PoolContainer __mPools;
		bool			__mIsInitial;
	};
}

#include "LBFactory.Inl"