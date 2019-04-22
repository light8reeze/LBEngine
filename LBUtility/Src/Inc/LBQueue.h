/**
	@file	LBQueue.h
	@brief	LBUtillity의 오브젝트 큐 관련 헤더
	@date	2019-04-21
	@auther Light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBUtility.h"
#include "LBLocker.h"

#ifdef _WINDOWS
#include <Windows.h>
#include <process.h>
#include <queue>

namespace LBNet
{
    /**
        @brief	        오브젝트 큐 클래스
		@details		세마포어를 이용한 큐 클래스.
        @param TObject	사용할 객체의 타입
        @date	        2019-04-21
        @auther         Light8reeze(light8reeze@gmail.com)
    */
	template<typename TObject>
	class CQueue
	{
	private:
		using ObjectQueue = std::queue<TObject>;

	public:
		CQueue();
		~CQueue();

		CQueue(const CQueue&) = delete;
		CQueue& operator=(const CQueue&) = delete;
	
		bool	Push(TObject& pObject);
		bool	Pop(TObject& pObject, bool pIsWait = false);

	private:
		HANDLE		__mSemaphore;
		ObjectQueue __mQueue;
		CLocker		__mLocker;
	};
};

#include "LBQueue.Inl"

#endif //_WINDOWS