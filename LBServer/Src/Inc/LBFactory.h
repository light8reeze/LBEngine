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
		CObjectPoolEx(int pSize) = default;
		virtual ~CObjectPoolEx() override;

		virtual void Initialize() override;
		virtual void Close() override;
	};

    /**
        @brief	        ������Ʈ ���丮
        @date	        2019-08-02
		@warning		������Ʈ�� ���� �� �ʱ�ȭ�� caller�� ���� �Ѵ�.
        @auther         light8reeze(light8reeze@gmail.com)
    */
	class LBS_EXPORT CFactory
	{
	public:
		template<typename TObject>
		using ObjectPtr = std::shared_ptr<TObject>;

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
		ObjectPtr<TObject> New();
		
		template<typename TObject>
		bool Delete(TObject*& pObject);
		
		template<typename TObject>
		static ObjectPtr<TObject> MakePtr(TObject*& pObject);

	private:
		static CFactory __mSingleton;
		__PoolContainer __mPools;
		bool			__mIsInitial;
	};
}

#include "LBFactory.Inl"