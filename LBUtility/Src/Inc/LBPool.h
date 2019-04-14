/**
	@file	LBPool.h
	@brief	LBUtillity�� ������Ʈ Ǯ���� ���
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
        @brief	        ������Ʈ Ǯ Ŭ����
		@details		������Ʈ Ǯ�� ������ ������ �ϴ�.
        @param TObject	����� ��ü�� Ÿ��
        @param TCount	������ ������Ʈ ����
        @date	        2019-04-10
        @todo           ���Ŀ� ���� �ܿ��� ���丮 Ŭ���� �ϼ��� ���� �׽�Ʈ�ϱ�
		@warning		������Ʈ�� ���� �� �ʱ�ȭ�� caller�� ���� �Ѵ�.
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