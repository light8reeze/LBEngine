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
#ifdef _WINDOWS
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