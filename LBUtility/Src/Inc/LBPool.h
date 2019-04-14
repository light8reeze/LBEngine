/**
	@file	LBPool.h
	@brief	LBUtillity의 오브젝트 풀관련 헤더
	@date	2019-04-10
	@auther Light8reeze(light8reeze@gmail.com)
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
        @param TCount	생성할 오브젝트 개수
        @date	        2019-04-10
        @todo           추후에 하위 단에서 팩토리 클래스 완성시 같이 테스트하기
		@warning		오브젝트를 받은 후 초기화는 caller가 직접 한다.
        @auther         Light8reeze(light8reeze@gmail.com)
    */
	template<class TObject, Size TCount>
	class CObjectPool
	{
	private:
		using ObjectQueue = std::queue<TObject*>;
		using ObjectArray = std::array<TObject*, TCount>;

	public:
		CObjectPool();
		~CObjectPool();

		CObjectPool(const CObjectPool&) = delete;
		CObjectPool& operator=(const CObjectPool& pCopy) = delete;
		CObjectPool& operator=(const CObjectPool&& pCopy) = delete;

		void		Initialize();
		void		Close();
		TObject*	NewObject();
		bool		DeleteObject(TObject*& pObject);

		constexpr Size GetMaxSize();
		Size GetUseSize();

	private:
		bool		__mIsAlloc;
		ObjectArray __mObjectArray;
		ObjectQueue	__mObjectQueue;
		Size		__mUseSize;
		CLocker		__mLocker;
	};
}

#include "LBPool.h"