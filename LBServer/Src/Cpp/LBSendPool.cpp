#include "LBSendPool.h"
#include "LBSender.h"

namespace LBNet
{
	CSendPool::CSendPool() : __mUseFlag(), __mChunkBuffer(nullptr),
		__mUseSize(0), __mMutex(), __mSenderList()
	{
	}

	CSendPool::~CSendPool()
	{
		SafeArrayDelete(__mChunkBuffer);
	}

	ErrCode CSendPool::Initialize(Size pChunkCnt)
	{
		LB_ASSERT(__mChunkBuffer == nullptr, "Error!");
		LB_ASSERT(__mUseSize == 0, "Error!");

		try
		{
			__mChunkBuffer = new CSendChunk[pChunkCnt];
		}
		catch (...)
		{
			LB_ASSERT(0, "bad Alloc!");
			return eErrCodeBadAlloc;
		}

		__mUseFlag.reserve(pChunkCnt);
		__mSenderList.reserve(pChunkCnt);
		__mChunkCnt = pChunkCnt;

		for (Size index = 0; index < pChunkCnt; ++index)
		{
			__mUseFlag.emplace_back(std::move(false));
			__mSenderList.emplace_back(std::move(CSender()));
		}

		return 0;
	}

	SharedObject<CSender> CSendPool::Allocate(Size pSendSize)
	{
		int aIndex = 0;
		Size aCnt = ((pSendSize + sizeof(SendHeader)) / sizeof(CSendChunk)) + 1;
		CSendChunk* aSendChunk = nullptr;
		CSender*	aSender = nullptr;

		{
			WriteLock aWriteLock(__mMutex);
			aIndex = GetAllocIndex(aCnt);

			if (aIndex == -1)
				return nullptr;

			aSendChunk = &(__mChunkBuffer[aIndex]);
			aSender = &(__mSenderList[aIndex]);

			for (int index = aIndex; index < (aIndex + aCnt); ++index)
			{
				__mUseFlag[index] = true;
			}

			__mUseSize += (aCnt * sizeof(CSendChunk));
		}

		aSender->SetSenderChunk(aSendChunk, aIndex, aCnt);

		auto aShared = SharedObject<CSender>(aSender, [this](CSender* pSender)
		{
			pSender->DeAllocate();
		});

		return aShared;
	}

	bool CSendPool::DeAllocate(int pIndex)
	{
		if (pIndex >= __mChunkCnt)
			return false;

		{
			WriteLock aWriteLock(__mMutex);

			if (__mUseFlag[pIndex] == false)
				return false;

			__mUseFlag[pIndex] = false;
			__mUseSize -= sizeof(CSendChunk);
		}

		return true;
	}

	int CSendPool::GetAllocIndex(Size pCnt)
	{
		int aMaxCnt = 0;
		int aAllocIndex = -1;
		int aFlagIndex = 0;

		for (auto aFlag : __mUseFlag)
		{
			if (!aFlag)
			{
				++aMaxCnt;

				if (aAllocIndex == -1)
					aAllocIndex = aFlagIndex;

				if (aMaxCnt == pCnt)
					break;
			}
			else
			{
				aMaxCnt = 0;
				aAllocIndex = -1;
			}

			++aFlagIndex;
		}

		return aAllocIndex;
	}

	Size CSendPool::GetUsableSize()
	{
		ReadLock aLock(__mMutex);
		return __mUseSize;
	}
}