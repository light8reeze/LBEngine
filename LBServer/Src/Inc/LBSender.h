/**
	@file	LBSender.h
	@brief	LBServer�� ��Ŷ ���� �޸� ���� �������
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
	constexpr Size eSzPacketMin = sizeof(CBufferHeader);		// �� ��Ŷ�� �ּ� ������

	/**
		@brief	��Ŷ ���ۿ� �޸� ���
		@date	2019-10-17
		@auther	light8reeze(light8reeze@gmail.com)
	*/
	class CSendChunk
	{
	public:
		char	mBuffer[eSzSendChunk];
	};

	/**
		@brief		��Ŷ ���ۿ� �޸� ����
		@comment	��� ����� Allocate -> GetWritePointer�� ���� �����͸� ������ -> CSession::Send�� ȣ���Ѵ�.
		@wranning	���۽� �Ҵ�޴� ������ ũ��� (����� ũ��(Size) + ��Ŷ�� ũ��)�̴�.
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
		// pSendSize : ���� ��Ŷ�� ũ��(��� ����)
		static SharedObject<CSender> Allocate(Size pSendSize);
		ErrCode		DeAllocate();
		ErrCode		Encrypt();

		void SetSenderChunk(CSendChunk* pChunk, int pChunkIndex, Size pChunkCnt);

		template<typename TObject>
		TObject*	GetWritePointer();
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