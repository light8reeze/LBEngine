/**
	@file	LBPool.h
	@brief	LBUtillity의 오브젝트 풀관련 헤더
	@date	2019-04-10
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include <queue>
#include "LBUtility.h"
#include "LBLocker.h"

namespace LBNet
{
    /**
        @brief	        오브젝트 풀 클래스
		@details		thread safe
        @param TObject	사용할 객체의 타입
        @date	        2019-04-10
		@warning		오브젝트를 받은 후 초기화는 caller가 직접 한다.
        @auther         light8reeze(light8reeze@gmail.com)
    */
	template<class TObject>
	class CObjectPool
	{
		LB_LOCKOBJECT(CObjectPool, CSharedMutex);

	public:
		using Type	= TObject;

	private:
		using __ObjectQueue	= std::queue<TObject*>;
		using __ObjectList	= std::vector<TObject*>;

	public:
		CObjectPool(Size pSize);
		~CObjectPool();

		CObjectPool(const CObjectPool&) = delete;
		CObjectPool& operator=(const CObjectPool&) = delete;

		void		Initialize();
		void		Close();
		TObject*	NewObject();
		bool		DeleteObject(TObject*& pObject);

		Size			GetMaxSize();
		Size			GetUseSize();
		constexpr Size	GetObjectSize();

	private:
		bool			__mIsAlloc;
		__ObjectList	__mObjectList;
		__ObjectQueue	__mObjectQueue;
		Size			__mUseSize;
		Size			__mPoolSize;
	};
}

#include "LBPool.Inl"