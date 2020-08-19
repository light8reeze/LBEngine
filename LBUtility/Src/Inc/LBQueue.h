/**
	@file	LBQueue.h
	@brief	LBUtillity�� ������Ʈ ť ���� ���
	@date	2019-04-21
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBUtility.h"
#include "LBLocker.h"

#ifdef _WINDOWS
#include <process.h>
#endif //_WINDOWS

namespace LBNet
{
    /**
        @brief	        ������Ʈ ť Ŭ����
		@details		������� �̿��� ť Ŭ����.
        @param TObject	����� ��ü�� Ÿ��
        @date	        2019-04-21
        @auther         light8reeze(light8reeze@gmail.com)
    */
	template<typename TObject>
	class CWaitableQueue
	{
		LB_LOCKOBJECT(CWaitableQueue, LBNet::CSharedMutex);

	private:
		using __ObjectQueue = std::queue<TObject>;

	public:
		CWaitableQueue();
		~CWaitableQueue();

		CWaitableQueue(const CWaitableQueue&) = delete;
		CWaitableQueue& operator=(const CWaitableQueue&) = delete;
	
		bool	Push(TObject& pObject);
		bool	Pop(TObject& pObject, unsigned long pWaitTime = 0);

	private:
		#ifdef _WINDOWS
		HANDLE			__mSemaphore;
		#endif //_WINDOWS
		__ObjectQueue	__mQueue;
	};
	
    /**
        @brief	        ���� ť Ŭ����
        @param TObject	����� ��ü�� Ÿ��
		@warning		������ �������� �������� �ʴ´�.
        @date	        2020-01-18
        @auther         light8reeze(light8reeze@gmail.com)
    */
	template<typename TObject>
	class CCircularQueue
	{
	public:
		CCircularQueue();
		~CCircularQueue();

		CCircularQueue(const CCircularQueue&) = delete;
		CCircularQueue& operator=(const CCircularQueue&) = delete;
		
		void		Initialize(Size pSize);
		bool		Push(TObject&& pObject);
		bool		Push(TObject& pObject);
		TObject&	Front();
		void		Pop();
		Size		GetUseSize();
		Size		GetMaxSize();
		bool		IsEmpty();
		bool		IsFull();

	private:
		TObject*	__mObjectQueue;
		int			__mPushIndex;
		int			__mPopIndex;
		Size		__mUseSize;
		Size		__mMaxSize;
	};
}

#include "LBQueue.Inl"