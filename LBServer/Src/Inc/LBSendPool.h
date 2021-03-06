/**
	@file	LBSendPool.h
	@brief	LBServer의 패킷 전송 메모리 관련 헤더파일
	@date	2019-10-17
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBServer.h"
#include "LBLocker.h"

namespace LBNet
{
	class CSender;
	class CSendChunk;

	/**
		@brief	        Send Buffer 풀 클래스
		@details		Send 메모리 블록을 관리한다.
		@date	        2019-10-17
		@auther         light8reeze(light8reeze@gmail.com)
	*/
	class LBS_EXPORT CSendPool
	{
		LB_LOCKOBJECT(CSendPool, CSharedMutex);
	private:
		using __UseFlag		= std::vector<bool>;
		using __SenderList	= std::vector<CSender>;

	public:
		CSendPool();
		~CSendPool();

		ErrCode					Initialize(Size pChunkCnt);
		SharedObject<CSender>	Allocate(Size pSendSize);
		bool					DeAllocate(int pIndex, Size pCnt);
		int						GetAllocIndex(Size pCnt);
		Size					GetUsableSize();

	private:
		CSendChunk*				__mChunkBuffer;
		#pragma warning(disable : 4251)
		__SenderList			__mSenderList;
		__UseFlag				__mUseFlag;
		#pragma warning(default : 4251)
		Size					__mChunkCnt;
		Size					__mUseSize;
	};
}