/**
	@file	LBMemory.h
	@brief	LBUtillity의 메모리관련 헤더
	@date	2019-03-29
	@auther Light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBUtility.h"
#include <array>
#include <memory>
#include <cstring>

namespace LBNet
{
    /**
        @brief	        버퍼 클래스
        @details        원형버퍼 구조로 데이터를 보관한다. 스레드에 안전하다.(추후 테스트)
        @param TSize			사용할 버퍼의 사이즈
        @param TMaxDataSize		버퍼에 넣을 데이터 단위 최대 사이즈
        @date	        2019-03-29
        @todo           원형버퍼 완성, 스레드 안정성 구현
        @auther         Light8reeze(light8reeze@gmail.com)
    */
    template<Size TSize, Size TMaxDataSize = TSize>
    class CBuffer
    {
	public:
		class CHeader
		{
		public:
			CHeader() = default;
			virtual ~CHeader() = default;

		public:
			Size mDataSize = 0;
		};

    public:
		CBuffer();
        virtual ~CBuffer()	= default;

        CBuffer(const CBuffer& pCopy)               = delete;
        CBuffer& operator=(const CBuffer& pCopy)    = delete;
		CBuffer& operator=(const CBuffer&& pCopy)	= delete;

    public:
        template<typename TData>
        bool Enqueue(const TData& pData);
        template<typename TData>
        bool Enqueue(TData&& pData);
		bool Enqueue(char* pData, int pSize);

        char* Dequeue();

        Size GetUsingSize();
		Size GetUsableSize();

		constexpr Size GetBufferSize();
		constexpr Size GetMaxDataSize();

	protected:
		//디버그 체크용 코드, 개발단계에서만 사용한다.
		void CheckBufferValid()
		{
			LB_ASSERT(__mCheckCode == 0xDEADBEEF && __mCheckCode2 == 0xDEADBEEF, "Invalid Buffer!");
			LB_ASSERT(__mUseSize <= GetBufferSize(), "Invalid Buffer!");
		}

    protected:
        Size	__mUseSize;
        int		__mReadIndex;
        int		__mWriteIndex;
		int		__mPassIndex;
        char	__mBuffer[TSize];
        DEBUG_CODE(char* __mCheckCode = 0xDEADBEEF); //메모리침범 체크를 위한 코드
		char	__mRestBuffer[TMaxDataSize + sizeof(CBuffer::CHeader)];
		DEBUG_CODE(char* __mCheckCode2 = 0xDEADBEEF); //메모리침범 체크를 위한 코드
	};
}

#include "LBMemory.Inl"