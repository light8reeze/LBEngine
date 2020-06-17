#include "LBSender.h"
#include "LBEncryption.h"

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
		LB_ASSERT(pSendSize >= sizeof(CPacketHeader), "Error");

		auto aShared = __mSendPool.Allocate(pSendSize + GetEncryptHdSize() + sizeof(SendHeader));

		if (aShared == nullptr)
			return nullptr;

		// 전송할 패킷의 크기를 미리 넣어준다.
		// 헤더의 크기를 제외한 크기가 들어간다.
		(reinterpret_cast<SendHeader*>(aShared->__mChunk))->mDataSize = pSendSize;

		return std::move(aShared);
	}

	ErrCode CSender::Encrypt()
	{
		if (CEncryptor::Instance() != nullptr)
		{
			auto aPtr = reinterpret_cast<char*>(__mChunk);
			aPtr += sizeof(SendHeader);

			return CEncryptor::Instance()->Encrypt(aPtr, GetSendSize() - sizeof(SendHeader));
		}

		return 0;
	}

	void CSender::SetSenderChunk(CSendChunk* pChunk, int pChunkIndex, Size pChunkCnt)
	{
		LB_ASSERT(pChunk != nullptr,	"Error");
		LB_ASSERT(pChunkIndex >= 0,		"Error");
		LB_ASSERT(pChunkCnt > 0,		"Error");
		LB_ASSERT(__mChunk == nullptr,	"Error");

		__mChunk		= pChunk;
		__mChunkIndex	= pChunkIndex;
		__mChunkCount	= pChunkCnt;
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

		return aDataSize + sizeof(SendHeader) + GetEncryptHdSize();
	}

	Size CSender::GetDataSize()
	{
		if (__mChunk == nullptr)
			return 0;

		return (reinterpret_cast<SendHeader*>(__mChunk))->mDataSize;
	}

	Size CSender::GetEncryptHdSize()
	{
		Size aEncryptHdSize = 0;

		if (CEncryptor::Instance() != nullptr)
			aEncryptHdSize = CEncryptor::Instance()->GetHeaderSize();

		return aEncryptHdSize;
	}

	ErrCode CSender::DeAllocate()
	{
		if (__mChunk == nullptr)
			return 0;

		LB_ASSERT(__mChunkIndex >= 0, "Error!");
		LB_ASSERT(__mChunkCount > 0, "Error!");
		
		int		aChunkIndex = __mChunkIndex;
		Size	aChunkCount = __mChunkCount;

		__mChunk = nullptr;
		__mChunkIndex = -1;
		__mChunkCount = 0;

		DEBUG_CODE(bool aResult = )
		__mSendPool.DeAllocate(aChunkIndex, aChunkCount);

		LB_ASSERT(aResult, "Send 반납 실패.");

		return 0;
	}
}