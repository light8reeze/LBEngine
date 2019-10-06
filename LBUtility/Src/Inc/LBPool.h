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
		@details		오브젝트 풀은 스레드 세이프 하다.
        @param TObject	사용할 객체의 타입
        @date	        2019-04-10
        @todo           추후에 하위 단에서 팩토리 클래스 완성시 같이 테스트하기
		@warning		오브젝트를 받은 후 초기화는 caller가 직접 한다.
        @auther         light8reeze(light8reeze@gmail.com)
    */
	template<class TObject>
	class CObjectPool
	{
	public:
		using Type	= TObject;

	private:
		using ObjectQueue	= std::queue<TObject*>;
		using ObjectList	= std::vector<TObject*>;

	public:
		CObjectPool(Size pSize);
		~CObjectPool();

		CObjectPool(const CObjectPool&) = delete;
		CObjectPool& operator=(const CObjectPool& pCopy) = delete;

		void		Initialize();
		void		Close();
		TObject*	NewObject();
		bool		DeleteObject(TObject*& pObject);

		Size GetMaxSize();
		Size GetUseSize();

	private:
		bool			__mIsAlloc;
		ObjectList		__mObjectList;
		ObjectQueue		__mObjectQueue;
		Size			__mUseSize;
		Size			__mPoolSize;
		CSharedMutex	__mMutex;
	};
}

#include "LBPool.Inl"