/**
	@file	LBPool.h
	@brief	LBUtillity�� ������Ʈ Ǯ���� ���
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
        @brief	        ������Ʈ Ǯ Ŭ����
		@details		thread safe
        @param TObject	����� ��ü�� Ÿ��
        @date	        2019-04-10
		@warning		������Ʈ�� ���� �� �ʱ�ȭ�� caller�� ���� �Ѵ�.
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