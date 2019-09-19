/**
	@file	LBBuffer.h
	@brief	LBUtillity의 버퍼관련 헤더
	@date	2019-03-29
	@auther light8reeze(light8reeze@gmail.com)
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
        @date	        2019-09-20
        @auther         light8reeze(light8reeze@gmail.com)
    */
    template<Size TSize>
    class CBuffer
    {
    public:
		CBuffer();
        virtual ~CBuffer()	= default;

        CBuffer(const CBuffer& pCopy)               = delete;
        CBuffer& operator=(const CBuffer& pCopy)    = delete;
		CBuffer& operator=(const CBuffer&& pCopy)	= delete;

    public:
		bool Push(const char* pData, int pSize);
		char* Front(Size& pSize, ErrCode& pErr);
		void Pop();
		void Clear();

        Size GetUsingSize() const;
		Size GetUsableSize() const;

		constexpr Size GetBufferSize() const;

    protected:
        Size				_mUseSize;
        int					_mReadIndex;
        int					_mWriteIndex;
        char				_mBuffer[TSize];
	};
	
    /**
        @brief	        비동기 버퍼 클래스
        @details        CBuffer을 확장하여 비동기 방식으로 Push를 가능하도록 확장한 클래스
		@warning		1.비동기 방식의 enqueue를 사용할때 넣을 데이터는 반드시 CBufferHeader를 상속받아라.
						2.비동기 enqueue는 WriteAddress받아 외부에서 처리하고, 비동기 처리가 끝나면 OnPush를 호출하여 사용한다.
        @param TSize			사용할 버퍼의 사이즈
        @param TMaxDataSize		버퍼에 넣을 데이터 단위 최대 사이즈
        @date	        2019-04-08
		@todo			비동기 Push 테스트하기(네트워크 클래스 개발되면 같이 테스트하기)
        @auther         light8reeze(light8reeze@gmail.com)
    */
	template<Size TSize, Size TMaxDataSize = TSize>
	class CAsyncBuffer : public CBuffer<TSize, TMaxDataSize>
	{
	public:
		bool  OnPush(int pSize);
		char* GetWriteAddress();
		Size  GetWritableSize() const;
	};
}

#include "LBBuffer.Inl"