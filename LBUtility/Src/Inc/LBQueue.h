/**
	@file	LBQueue.h
	@brief	LBUtillity의 오브젝트 큐 관련 헤더
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
        @brief	        오브젝트 큐 클래스
		@details		세마포어를 이용한 큐 클래스.
        @param TObject	사용할 객체의 타입
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
        @brief	        원형 큐 클래스
        @param TObject	사용할 객체의 타입
		@warning		스레드 안정성은 보장하지 않는다.
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