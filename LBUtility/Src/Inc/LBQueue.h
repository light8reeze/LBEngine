/**
	@file	LBQueue.h
	@brief	LBUtillity�� ������Ʈ ť ���� ���
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
        @brief	        ������Ʈ ť Ŭ����
		@details		������� �̿��� ť Ŭ����.
        @param TObject	����� ��ü�� Ÿ��
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