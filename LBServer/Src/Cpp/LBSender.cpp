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

		// 전송할 패킷의 크기를 미리 넣어준다.
		// 헤더의 크기를 제외한 크기가 들어간다.
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

			LB_ASSERT(aResult, "Send가 반납되지 못했다.");
		}

		__mChunk = nullptr;
		__mChunkIndex = -1;
		__mChunkCount = 0;

		return 0;
	}
}