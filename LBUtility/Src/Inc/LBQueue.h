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
#ifdef _WINDOWS
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
	private:
		using __ObjectQueue = std::queue<TObject>;

	public:
		CWaitableQueue();
		~CWaitableQueue();

		CWaitableQueue(const CWaitableQueue&) = delete;
		CWaitableQueue& operator=(const CWaitableQueue&) = delete;
	
		bool	Push(TObject& pObject);
		bool	Pop(TObject& pObject, bool pIsWait = false);

	private:
		HANDLE			__mSemaphore;
		__ObjectQueue	__mQueue;
		CSharedMutex	__mMutex;
	};
#endif //_WINDOWS
}

#include "LBQueue.Inl"