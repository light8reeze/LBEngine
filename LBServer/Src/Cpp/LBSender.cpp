#include "LBSender.h"

namespace LBNet
{
	CSendPool CSender::__mSendPool;

	CSender::CSender() : __mChunk(nullptr), __mChunkIndex(-1), __mChunkCount(0)
	{
	}

	CSender::~CSender()
	{
	}

	ErrCode CSender::Initialize(Size pSendCnt)
	{
		return __mSendPool.Initialize(pSendCnt);
	}

	SharedObject<CSender> CSender::Allocate(Size pSendSize)
	{
		auto aShared = __mSendPool.Allocate(pSendSize);

		if (aShared == nullptr)
			return nullptr;

		// ������ ��Ŷ�� ũ�⸦ �̸� �־��ش�.
		// ����� ũ�⸦ ������ ũ�Ⱑ ����.
		(reinterpret_cast<SendHeader*>(aShared->__mChunk))->mDataSize = pSendSize;

		return std::move(aShared);
	}

	void* CSender::GetSendPointer()
	{
		return (reinterpret_cast<void*>(__mChunk));
	}

	Size CSender::GetSendSize()
	{
		Size aDataSize = GetDataSize();

		if (aDataSize == 0)
			return 0;

		return aDataSize + sizeof(SendHeader);
	}

	Size CSender::GetDataSize()
	{
		if (__mChunk == nullptr)
			return 0;

		return (reinterpret_cast<SendHeader*>(__mChunk))->mDataSize;
	}

	ErrCode CSender::__DeAllocate()
	{
		if (__mChunk == nullptr)
			return 0;

		LB_ASSERT(__mChunkIndex > 0, "Error!");
		LB_ASSERT(__mChunkCount > 0, "Error!");

		for (int index = __mChunkIndex; index < (__mChunkIndex + __mChunkCount); ++index)
		{
			bool aResult = __mSendPool.DeAllocate(index);

			LB_ASSERT(aResult, "Send�� �ݳ����� ���ߴ�.");
		}

		__mChunk = nullptr;
		__mChunkIndex = -1;
		__mChunkCount = 0;

		return 0;
	}
}