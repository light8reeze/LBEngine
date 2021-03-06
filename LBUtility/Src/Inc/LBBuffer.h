﻿/**
	@file	LBBuffer.h
	@brief	LBUtillity의 버퍼관련 헤더
	@date	2019-03-29
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBUtility.h"

namespace LBNet
{
	/**
		@brief	        버퍼헤더 클래스
		@date	        2019-03-29
		@auther         light8reeze(light8reeze@gmail.com)
	*/
	#pragma pack(push, 1)
	class CBufferHeader
	{
	public:
		CBufferHeader() = default;
		~CBufferHeader() = default;

	public:
		Size mDataSize = 0;	// 헤더를 제외한 사이즈이다.
	};
	#pragma pack(pop)

    /**
        @brief	        버퍼 클래스
		@warning		1.비동기 방식의 enqueue를 사용할때 넣을 데이터는 반드시 CBufferHeader를 상속받아라.
						2.비동기 enqueue는 WriteAddress받아 외부에서 처리하고, 비동기 처리가 끝나면 OnPush를 호출하여 사용한다.
						3.스레드 안정성은 보장하지 않는다.
						(서버 패킷 receive(Push)->패킷 처리(pop)를 한스레드에서 하는걸 고려해서 개발)
						4.버퍼의 데이터를 모두 처리후 반드시 Pop를 호출해야 한다.
						(Push -> Front -> Pop 순서로 사용한다.)
        @date	        2019-03-29
        @auther         light8reeze(light8reeze@gmail.com)
    */
	class LBU_EXPORT CBuffer
	{
	public:
		CBuffer(Size pSize);
		~CBuffer();

		CBuffer(const CBuffer&) = delete;
		CBuffer& operator=(const CBuffer&) = delete;
		CBuffer& operator=(const CBuffer&&) = delete;

	public:
		bool	Push(const char* pData, Size pSize);
		char*	Front(Size& pSize, ErrCode& pErr);
		void	Pop();
		void	Clear();
		bool	OnPush(Size pSize);
		char*	GetWritePointer();

		Size GetUsingSize() const;
		Size GetUsableSize() const;

		Size GetBufferSize();

	protected:
		const Size	_mMAX_SIZE;
		Size		_mUseSize;
		int			_mReadIndex;
		int			_mWriteIndex;
		char*		_mBuffer;
	};
}