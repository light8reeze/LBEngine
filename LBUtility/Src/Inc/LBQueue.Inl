namespace LBNet
{
	#ifdef _WINDOWS
	template<typename TObject>
	CWaitableQueue<TObject>::CWaitableQueue() : __mSemaphore(NULL), __mQueue(), __mMutex()
	{
		__mSemaphore = ::CreateSemaphore(NULL, 0, 0xFFFFFF, NULL);
		LB_ASSERT(__mSemaphore != NULL, "Create Semaphore Error!");
	}

	template<typename TObject>
	CWaitableQueue<TObject>::~CWaitableQueue()
	{
		::CloseHandle(__mSemaphore);
	}

	template<typename TObject>
	bool CWaitableQueue<TObject>::Push(TObject& pObject)
	{
		{
			WriteLock aLocker(_mLocker);
			__mQueue.push(pObject);
		}

		BOOL bResult = ::ReleaseSemaphore(__mSemaphore, 1, NULL);
		LB_ASSERT(bResult, "Release Semaphore Error!");

		return true;
	}

	template<typename TObject>
	bool CWaitableQueue<TObject>::Pop(TObject& pObject, unsigned long pWaitTime)
	{
		DWORD dwResult = ::WaitForSingleObject(__mSemaphore, pWaitTime);

		if (dwResult != WAIT_OBJECT_0)
		{
			if (dwResult != WAIT_TIMEOUT)
			{
				LB_ASSERT(0, "Invalid Dequeue!");
			}

			return false;
		}

		{
			WriteLock aLocker(_mLocker);
			pObject = __mQueue.front();
			__mQueue.pop();
		}

		return true;
	}
	#endif //_WINDOWS

	template<typename TObject>
	CCircularQueue<TObject>::CCircularQueue() : __mObjectQueue(nullptr), __mPushIndex(0),
		__mPopIndex(0), __mUseSize(0), __mMaxSize(0)
	{
	}

	template<typename TObject>
	CCircularQueue<TObject>::~CCircularQueue()
	{
		SafeArrayDelete(__mObjectQueue);
	}

	template<typename TObject>
	void CCircularQueue<TObject>::Initialize(Size pSize)
	{
		LB_ASSERT(__mObjectQueue == nullptr, "Init Twice");

		__mObjectQueue = new TObject[pSize];
		__mMaxSize = pSize;
	}

	template<typename TObject>
	bool CCircularQueue<TObject>::Push(TObject&& pObject)
	{
		LB_ASSERT(__mObjectQueue != nullptr, "Initialize First");
		LB_ASSERT(__mMaxSize > 0, "Initialize First");

		if (__mUseSize == __mMaxSize)
			return false;

		__mObjectQueue[__mPushIndex] = std::move(pObject);

		if (__mPushIndex == __mPopIndex)
			__mPopIndex = __mPushIndex;

		__mPushIndex = (__mPushIndex + 1) % static_cast<int>(__mMaxSize);
		++__mUseSize;

		return true;
	}

	template<typename TObject>
	bool CCircularQueue<TObject>::Push(TObject& pObject)
	{
		LB_ASSERT(__mObjectQueue != nullptr, "Initialize First");
		LB_ASSERT(__mMaxSize > 0, "Initialize First");

		if (__mUseSize == __mMaxSize)
			return false;

		__mObjectQueue[__mPushIndex] = pObject;

		if (__mPushIndex == __mPopIndex)
			__mPopIndex = __mPushIndex;

		__mPushIndex = (__mPushIndex + 1) % static_cast<int>(__mMaxSize);
		++__mUseSize;

		return true;
	}


	template<typename TObject>
	TObject& CCircularQueue<TObject>::Front()
	{
		LB_ASSERT(__mObjectQueue != nullptr, "Initialize First");
		LB_ASSERT(__mMaxSize > 0, "Initialize First");

		return __mObjectQueue[__mPopIndex];
	}

	template<typename TObject>
	void CCircularQueue<TObject>::Pop()
	{
		LB_ASSERT(__mObjectQueue != nullptr, "Initialize First");
		LB_ASSERT(__mMaxSize > 0, "Initialize First");

		if (__mPopIndex == __mPushIndex)
			return;

		__mPopIndex = (__mPopIndex + 1) % __mMaxSize;
		--__mUseSize;
	}

	template<typename TObject>
	Size CCircularQueue<TObject>::GetUseSize()
	{
		LB_ASSERT(__mObjectQueue != nullptr, "Initialize First");
		LB_ASSERT(__mMaxSize > 0, "Initialize First");

		return __mUseSize;
	}

	template<typename TObject>
	Size CCircularQueue<TObject>::GetMaxSize()
	{
		LB_ASSERT(__mObjectQueue != nullptr, "Initialize First");
		LB_ASSERT(__mMaxSize > 0, "Initialize First");

		return __mMaxSize;
	}

	template<typename TObject>
	bool CCircularQueue<TObject>::IsEmpty()
	{
		LB_ASSERT(__mObjectQueue != nullptr, "Initialize First");
		LB_ASSERT(__mMaxSize > 0, "Initialize First");

		return (__mUseSize == 0);
	}

	template<typename TObject>
	bool CCircularQueue<TObject>::IsFull()
	{
		LB_ASSERT(__mObjectQueue != nullptr, "Initialize First");
		LB_ASSERT(__mMaxSize > 0, "Initialize First");

		return (__mUseSize == __mMaxSize);
	}
}