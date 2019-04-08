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
    /**
        @brief	        버퍼헤더 클래스
        @date	        2019-03-29
        @auther         Light8reeze(light8reeze@gmail.com)
    */
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
		@warning		Enqueue를 동시에 하거나 Dequeue를 동시에 하면 쓰레드 세이프 하지 않는다.
						(Enqueue, Dequeue를 동시에 하는건 쓰레드 세이프하다.)
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
			LB_ASSERT(_mUseSize <= GetBufferSize(), "Invalid Buffer!");
			#pragma warning(default : 4312)
		}

    protected:
		CLocker				_mLocker;
        Size				_mUseSize;
        int					_mReadIndex;
        int					_mWriteIndex;
		std::atomic<int>	_mPassIndex;
        char				_mBuffer[TSize];

	private:
        DEBUG_CODE(char*	__mCheckCode); //메모리침범 체크를 위한 코드
		char				__mRestBuffer[TMaxDataSize + sizeof(CBufferHeader)];
		DEBUG_CODE(char*	__mCheckCode2); //메모리침범 체크를 위한 코드
	};
	
    /**
        @brief	        비동기 버퍼 클래스
        @details        CBuffer을 확장하여 비동기 방식으로 Enqueue를 가능하도록 확장한 클래스
		@warning		1.비동기 방식의 enqueue를 사용할때 넣을 데이터는 반드시 CBufferHeader를 상속받아라.
						2.비동기 enqueue는 WriteAddress받아 외부에서 처리하고, 비동기 처리가 끝나면 OnEnqueue를 호출하여 사용한다.
        @param TSize			사용할 버퍼의 사이즈
        @param TMaxDataSize		버퍼에 넣을 데이터 단위 최대 사이즈
        @date	        2019-04-08
		@todo			비동기 Enqueue 테스트하기(네트워크 클래스 개발되면 같이 테스트하기)
        @auther         Light8reeze(light8reeze@gmail.com)
    */
	template<Size TSize, Size TMaxDataSize = TSize>
	class CAsyncBuffer : public CBuffer<TSize, TMaxDataSize>
	{
	public:
		bool  OnEnqueue(int pSize);
		char* GetWriteAddress();
		Size  GetWritableSize() const;
	};
}

#include "LBBuffer.Inl"