/**
	@file	LBCircularBuffer.h
	@brief	LBUtillity의 버퍼관련 헤더
	@date	2019-03-29
	@auther Light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBUtility.h"
#include <array>
#include <memory>

namespace LBNet
{
    /**
        @brief	        버퍼 보관용 클래스
        @details        원형버퍼 구조로 데이터를 보관한다. 스레드에 안전하다.(추후 테스트)
        @param TSize    사용할 버퍼의 사이즈
        @date	        2019-03-29
        @todo           원형버퍼 완성, 스레드 안정성 구현
        @auther         Light8reeze(light8reeze@gmail.com)
    */
    template<Size TSize>
    class CCircularBuffer
    {
    private:
        using BufferType = std::array<char, TSize>;

    public:
        template<typename TData>
        class CData
        {
        public:
            CData() = delete;
            ~CData() = delete;
            CData(const TData* pData);

            TData& operator*();
            TData* operator->();

        private:
            std::shared_ptr<TData> __mDataPtr;
        }

    public:
        CCircularBuffer()   = default;
        ~CCircularBuffer()  = default;

        CCircularBuffer(const CCircularBuffer& pCopy)               = delete;
        CCircularBuffer& operator=(const CCircularBuffer& pCopy)    = delete;

    public:
        template<typename TData>
        bool Enqueue(const TData& pData);
        template<typename TData>
        bool Enqueue(TData&& pData);
        bool EnqueueAsync(int pSize);

        template<typename TData>
        TData*  Dequeue();
        char*   Dequeue(int pSize);

        int GetUsingSize();

        constexpr Size GetBufferSize() { return TSize; }

    private:
        int         __mUseSize;
        int         __mReadIndex;
        int         __mWriteIndex;
        BufferType  __mBuffer;
        
        ONLY_DEBUG(char* __mCheckCode = 0xDEADBEEF); //메모리침범 체크를 위한 코드
    };
}

#include "LBCircularBuffer.Inl"