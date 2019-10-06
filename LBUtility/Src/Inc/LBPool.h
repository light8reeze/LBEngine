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
		@details		������Ʈ Ǯ�� ������ ������ �ϴ�.
        @param TObject	����� ��ü�� Ÿ��
        @date	        2019-04-10
        @todo           ���Ŀ� ���� �ܿ��� ���丮 Ŭ���� �ϼ��� ���� �׽�Ʈ�ϱ�
		@warning		������Ʈ�� ���� �� �ʱ�ȭ�� caller�� ���� �Ѵ�.
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