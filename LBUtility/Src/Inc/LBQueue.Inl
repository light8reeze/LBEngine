namespace LBNet
{
	template<typename TObject>
	CQueue<TObject>::CQueue() : __mSemaphore(NULL), __mQueue(), __mLocker()
	{
		__mSemaphore = ::CreateSemaphore(NULL, 0, 0xFFFFFF, NULL);
		LB_ASSERT(__mSemaphore != NULL, "Create Semaphore Error!");
	}

	template<typename TObject>
	CQueue<TObject>::~CQueue()
	{
		::CloseHandle(__mSemaphore);
	}

	template<typename TObject>
	bool CQueue<TObject>::Push(TObject& pObject)
	{
		{
			std::unique_lock<CLocker> aLocker(__mLocker);
			__mQueue.push(pObject);
			BOOL bResult = ::ReleaseSemaphore(__mSemaphore, 1, NULL);

			LB_ASSERT(bResult, "Release Semaphore Error!");
		}

		return true;
	}

	template<typename TObject>
	bool CQueue<TObject>::Pop(TObject& pObject, bool pIsWait)
	{
		DWORD dwResult = ::WaitForSingleObject(__mSemaphore, (pIsWait)? INFINITE : 0);

		if (dwResult != WAIT_OBJECT_0)
		{
			if (dwResult != WAIT_TIMEOUT)
			{
				LB_ASSERT(0, "Invalid Dequeue!");
			}

			return false;
		}

		{
			std::unique_lock<CLocker> aLocker(__mLocker);
			pObject = __mQueue.front();
			__mQueue.pop();
		}

		return true;
	}
}