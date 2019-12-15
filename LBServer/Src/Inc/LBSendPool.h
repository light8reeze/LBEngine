/**
	@file	LBSendPool.h
	@brief	LBServer�� ��Ŷ ���� �޸� ���� �������
	@date	2019-10-17
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#pragma warning(disable : 4251)
#include "LBServer.h"
#include "LBLocker.h"

namespace LBNet
{
	class CSender;
	class CSendChunk;

	// warning C4251 ó��
	// vector�� ��� �ν��Ͻ�ȭ ��Ų��.<L7>
	LBS_EXPORT_TEMPLATE(std::vector<bool>);
	LBS_EXPORT_TEMPLATE(std::vector<CSender>);

	/**
		@brief	        Send Buffer Ǯ Ŭ����
		@details		Send �޸� ����� �����Ѵ�.
		@date	        2019-10-17
		@auther         light8reeze(light8reeze@gmail.com)
	*/
	class LBS_EXPORT CSendPool
	{
	private:
		using __UseFlag		= std::vector<bool>;
		using __SenderList	= std::vector<CSender>;

	public:
		CSendPool();
		~CSendPool();

		ErrCode					Initialize(Size pChunkCnt);
		SharedObject<CSender>	Allocate(Size pSendSize);
		bool					DeAllocate(int pIndex);
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
		CSharedMutex			__mMutex;
	};
}
#pragma warning(default : 4251)