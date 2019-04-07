/**
	@file	LBBuffer.h
	@brief	LBUtillity의 버퍼관련 헤더
	@date	2019-03-29
	@auther Light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBUtility.h"
#include "LBLocker.h"
#include <array>
#include <memory.h>
#include <string.h>
#include <atomic>

namespace LBNet
{
	class CBufferHeader
	{
	public:
		CBufferHeader() = default;
		~CBufferHeader() = default;

	public:
		Size mDataSize = 0;
	};

    /**
        @brief	        버퍼 클래스
        @details        원형버퍼 구조로 데이터를 보관한다. 스레드에 안전하다.(추후 테스트)
        @param TSize			사용할 버퍼의 사이즈
        @param TMaxDataSize		버퍼에 넣을 데이터 단위 최대 사이즈
        @date	        2019-03-29
        @todo           이동방식 Enqueue 구현
        @auther         Light8reeze(light8reeze@gmail.com)
    */
    template<Size TSize, Size TMaxDataSize = TSize>
    class CBuffer
    {
    public:
		CBuffer();
        virtual ~CBuffer()	= default;

        CBuffer(const CBuffer& pCopy)               = delete;
        CBuffer& operator=(const CBuffer& pCopy)    = delete;
		CBuffer& operator=(const CBuffer&& pCopy)	= delete;

    public:
        template<typename TData>
        bool Enqueue(const TData& pData);
        //template<typename TData>
        //bool Enqueue(TData&& pData);
		bool Enqueue(const char* pData, int pSize);

        char* Dequeue();

        Size GetUsingSize() const;
		Size GetUsableSize() const;

		constexpr Size GetBufferSize() const;
		constexpr Size GetMaxDataSize() const;

	protected:
		//디버그 체크용 코드, 개발단계에서만 사용한다.
		void CheckBufferValid()
		{
			#pragma warning(disable : 4312)
			LB_ASSERT(__mCheckCode == reinterpret_cast<char*>(0xDEADBEEFDEADBEEF) && __mCheckCode2 == reinterpret_cast<char*>(0xDEADBEEFDEADBEEF), "Invalid Buffer!");
			LB_ASSERT(__mUseSize <= GetBufferSize(), "Invalid Buffer!");
			#pragma warning(default : 4312)
		}

    protected:
		CLocker				__mLocker;
        Size				__mUseSize;
        int					__mReadIndex;
        int					__mWriteIndex;
		std::atomic<int>	__mPassIndex;
        char				__mBuffer[TSize];
        DEBUG_CODE(char*	__mCheckCode); //메모리침범 체크를 위한 코드
		char				__mRestBuffer[TMaxDataSize + sizeof(CBufferHeader)];
		DEBUG_CODE(char*	__mCheckCode2); //메모리침범 체크를 위한 코드
	};
}

#include "LBBuffer.Inl"