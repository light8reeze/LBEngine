/**
	@file	LBSender.h
	@brief	LBServer의 패킷 전송 메모리 관련 헤더파일
	@date	2019-10-17
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBServer.h"
#include "LBSendPool.h"
#include "LBBuffer.h"
#include "LBHandler.h"

namespace LBNet
{
	using SendHeader = CBufferHeader;
	constexpr Size eSzPacketMin = sizeof(SendHeader);		// 한 패킷당 최소 사이즈

	/**
		@brief	패킷 전송용 메모리 블록
		@date	2019-10-17
		@auther	light8reeze(light8reeze@gmail.com)
	*/
	class CSendChunk
	{
	public:
		char	mBuffer[eSzSendChunk];
	};

	/**
		@brief		패킷 전송용 메모리 단위
		@comment	사용 방법은 Allocate -> GetWritePointer를 통해 데이터를 넣은후 -> CSession::Send를 호출한다.
		@wranning	전송시 할당받는 버퍼의 크기는 (헤더의 크기(Size) + 패킷의 크기)이다.
		@date		2019-10-17
		@auther		light8reeze(light8reeze@gmail.com)
	*/
	class LBS_EXPORT CSender
	{
	public:
		CSender();
		~CSender();

		static ErrCode Initialize(Size pSendCnt);

		template<typename TObject>
		static SharedObject<CSender> Allocate();
		// pSendSize : 순수 패킷의 크기(헤더 제외)
		static SharedObject<CSender> Allocate(Size pSendSize);
		ErrCode		DeAllocate();
		ErrCode		Encrypt();

		void SetSenderChunk(CSendChunk* pChunk, int pChunkIndex, Size pChunkCnt);

		template<typename TObject>
		TObject*	GetWritePointer();
		template<typename TObject>
		void		SetData(TObject& pObject);
		void*		GetSendPointer();
		Size		GetSendSize();
		Size		GetDataSize();
		static Size	GetEncryptHdSize();

	private:
		CSendChunk*		__mChunk;
		int				__mChunkIndex;
		Size			__mChunkCount;

		static CSendPool __mSendPool;
	};
}

#include "LBSender.Inl"