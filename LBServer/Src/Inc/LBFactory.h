/**
	@file	LBFactory.h
	@brief	LBServer의 팩토리 관련 헤더파일
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
		@brief	        오브젝트 풀 확장 클래스
		@details		팩토리에서 관리를 위해 CObjectPool클래스를 확장한다.	
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
        @brief	        오브젝트 팩토리
        @date	        2019-08-02
		@warning		오브젝트를 받은 후 초기화는 caller가 직접 한다.
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