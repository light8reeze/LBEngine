#include "LBQueue.h"
#include <sstream>
namespace LBNet
{
	/**
		@brief CBuffer의 생성자
	*/
	template<Size TSize, Size TMaxDataSize>
	CBuffer<TSize, TMaxDataSize>::CBuffer() : _mUseSize(0), _mReadIndex(-1), _mWriteIndex(0), 
		_mPassIndex(-1), _mBuffer(), __mRestBuffer()
	{
		#pragma warning(disable : 4312)
		DEBUG_CODE(__mCheckCode = reinterpret_cast<char*>(0xDEADBEEFDEADBEEF));
		DEBUG_CODE(__mCheckCode2 = reinterpret_cast<char*>(0xDEADBEEFDEADBEEF));
		#pragma warning(default : 4312)
	}

	/**
		@brief 버퍼에 데이터를 넣는 함수
		@param const TData& 버퍼에 넣을 데이터
		@return bool 버퍼에 데이터를 넣은 결과
	*/
	template<Size TSize, Size TMaxDataSize>
	template<typename TData>
	bool CBuffer<TSize, TMaxDataSize>::Push(const TData& pData)
	{
		return Push(reinterpret_cast<const char*>(&pData), sizeof(TData));
	}

	template<Size TSize, Size TMaxDataSize>
	bool CBuffer<TSize, TMaxDataSize>::Push(const char* pData, int pSize)
	{
		Size aDataSize = sizeof(CBufferHeader) + pSize;
		LB_ASSERT(pSize <= GetMaxDataSize(), "Data size is too big!!");

		Size aCopyableSize = 0;
		Size aRestSize = 0;

		int aReadIndex		= 0;
		int aWriteIndex		= 0;
		Size aUsableSize	= 0;
		Size aPassSize		= 0;
		bool aCheckPass = false;

		{
			std::unique_lock<CLocker> aLocker(_mLocker);
			
			aReadIndex = _mReadIndex;
			aWriteIndex = _mWriteIndex;
			aUsableSize = GetUsableSize();
			aPassSize = 0;
		}

		if (aDataSize > aUsableSize)
			return false;

		aCopyableSize = (aReadIndex > aWriteIndex) ? aReadIndex - aWriteIndex : GetBufferSize() - aWriteIndex;

		if (sizeof(CBufferHeader) > GetBufferSize() - aWriteIndex)
		{
			_mPassIndex = aWriteIndex;
			aWriteIndex = 0;
			aCopyableSize = aDataSize;
			aPassSize = GetBufferSize() - _mPassIndex;
			aCheckPass = true;
		}
		else if (aDataSize > aCopyableSize)
			aRestSize = aDataSize - aCopyableSize;
		else
			aCopyableSize = aDataSize;

		CBufferHeader* aHeader = reinterpret_cast<CBufferHeader*>(_mBuffer + aWriteIndex);
		aHeader->mDataSize = pSize;

		aCopyableSize	-= sizeof(CBufferHeader);
		aWriteIndex		+= sizeof(CBufferHeader);

		if (aWriteIndex == static_cast<int>(GetBufferSize()))
			aWriteIndex = 0;

		LB_ASSERT(aWriteIndex <= static_cast<int>(GetBufferSize()), "Invalid Write Index");
		::memcpy_s(_mBuffer + aWriteIndex, aCopyableSize, pData, aCopyableSize);
		aWriteIndex += aCopyableSize;

		if (aRestSize > 0)
		{
			LB_ASSERT(aRestSize + aCopyableSize + sizeof(CBufferHeader) == aDataSize, "Wrong Size!");
			::memcpy_s(_mBuffer, GetUsableSize() - aCopyableSize, pData + aCopyableSize, aRestSize);
			aWriteIndex = aRestSize;
		}

		LB_ASSERT(aWriteIndex <= static_cast<int>(GetBufferSize()), "Wrong Index");
		if (aWriteIndex == static_cast<int>(GetBufferSize()))
			aWriteIndex = 0;

		{
			std::unique_lock<CLocker> aLocker(_mLocker);
			
			if (_mWriteIndex + aDataSize != aWriteIndex)
			{
				if (aWriteIndex + ((aCheckPass)? _mPassIndex.load() : GetBufferSize()) != _mWriteIndex + aDataSize)
				{
					LB_ASSERT(0, "s");
				}
			}

			if (_mReadIndex == -1)
				_mReadIndex = _mWriteIndex;

			_mWriteIndex	= aWriteIndex;
			_mUseSize		+= (aDataSize + aPassSize);
		}

		CheckBufferValid();
		return true;
	}

	template<Size TSize, Size TMaxDataSize>
	char* CBuffer<TSize, TMaxDataSize>::Pop()
	{
		CBufferHeader* aHeader = nullptr;
		int aReadIndex	= 0;
		int aWriteIndex = 0;
		int aPassIndex	= 0;
		int aPassSize	= 0;
		
		if (GetUsingSize() < sizeof(CBufferHeader) || _mReadIndex == -1)
			return nullptr;

		LB_ASSERT(_mReadIndex != -1, "Wrong Index!");
		
		{
			std::unique_lock<CLocker> aLocker(_mLocker);

			aReadIndex = _mReadIndex;
			aWriteIndex = _mWriteIndex;
			aPassIndex = _mPassIndex.load();
		}

		int aLastIndex = (aPassIndex == -1) ? GetBufferSize() - 1 : aPassIndex - 1;

		if (aReadIndex >= aLastIndex)
		{
			aReadIndex = 0;

			if (aPassIndex != -1)
			{
				aPassSize	= GetBufferSize() - _mPassIndex;
				_mPassIndex = aPassIndex = -1;
			}
		}

		LB_ASSERT(aReadIndex + sizeof(CBufferHeader) <= aLastIndex + 1, "Invalid Buffer!");
		aHeader		= reinterpret_cast<CBufferHeader*>(_mBuffer + aReadIndex);
		aReadIndex += sizeof(CBufferHeader);
		
		LB_ASSERT(aHeader->mDataSize <= TSize, "Invalid! Size");
		LB_ASSERT(aHeader->mDataSize < TMaxDataSize, "Invalid! Size");
		if (GetUsingSize() < sizeof(CBufferHeader) + aHeader->mDataSize)
			return nullptr;

		LB_ASSERT(aLastIndex < static_cast<int>(GetBufferSize()), "Wrong Index!");

		char* aData = nullptr;
		if (aReadIndex + static_cast<int>(aHeader->mDataSize) > aLastIndex + 1)
		{
			int aMaxIndex = aReadIndex + aHeader->mDataSize;
			int aCopySize = (aLastIndex - aReadIndex + 1);
			int aRestSize = (static_cast<int>(aHeader->mDataSize) - aCopySize);
			LB_ASSERT(aRestSize > 0, "Wrong Size!");

			::memcpy_s(__mRestBuffer, TMaxDataSize + sizeof(CBufferHeader), reinterpret_cast<const void*>(_mBuffer + aReadIndex), aCopySize);
			::memcpy_s(__mRestBuffer + aCopySize, TMaxDataSize + sizeof(CBufferHeader) - aCopySize, reinterpret_cast<const void*>(_mBuffer), aRestSize);

			aData		= __mRestBuffer;
			aReadIndex	= aRestSize;

			if (aPassIndex != -1)
				_mPassIndex = -1;
		}
		else
		{
			aData		= _mBuffer + aReadIndex;
			aReadIndex += aHeader->mDataSize;

			if (aReadIndex == aLastIndex + 1)
			{
				aReadIndex = 0;

				if (aPassIndex != -1)
					_mPassIndex = -1;
			}

			LB_ASSERT(aReadIndex <= aLastIndex, "Wrong Index");
		}

		{
			std::unique_lock<CLocker> aLocker(_mLocker);
			_mReadIndex = aReadIndex;
			_mUseSize	-= (aHeader->mDataSize + sizeof(CBufferHeader) + aPassSize);
		}

		CheckBufferValid();
		return aData;
	}

	template<Size TSize, Size TMaxDataSize>
	Size CBuffer<TSize, TMaxDataSize>::GetUsingSize() const
	{
		return _mUseSize;
	}

	template<Size TSize, Size TMaxDataSize>
	Size CBuffer<TSize, TMaxDataSize>::GetUsableSize() const
	{
		return GetBufferSize() - _mUseSize;
	}

	template<Size TSize, Size TMaxDataSize>
	constexpr Size CBuffer<TSize, TMaxDataSize>::GetBufferSize() const
	{
		static_assert(TSize > 0);
		return TSize;
	}

	template<Size TSize, Size TMaxDataSize>
	constexpr Size CBuffer<TSize, TMaxDataSize>::GetMaxDataSize() const
	{
		static_assert(TMaxDataSize > 0);
		return TMaxDataSize;
	}

	template<Size TSize, Size TMaxDataSize>
	bool CAsyncBuffer<TSize, TMaxDataSize>::OnPush(int pSize)
	{
		LB_ASSERT(pSize >= sizeof(CBufferHeader),	"Invalid Enqueue!");
		LB_ASSERT(GetUsableSize() >= pSize,			"Invalid Size!");
		
		std::unique_lock<CLocker> aLocker(_mLocker);
		_mWriteIndex	+= pSize;
		_mUseSize		+= static_cast<Size>(pSize);

		LB_ASSERT(_mWriteIndex < TSize, "Invalid Index!");

		if (_mWriteIndex == TSize)
			_mWriteIndex = 0;
		else if (GetWritableSize() < sizeof(CBufferHeader))
		{
			_mPassIndex		= _mWriteIndex;
			_mWriteIndex	= 0;
		}

		if (_mReadIndex == -1)
			_mReadIndex = 0;

		CheckBufferValid();
		return true;
	}

	template<Size TSize, Size TMaxDataSize>
	char* CAsyncBuffer<TSize, TMaxDataSize>::GetWriteAddress()
	{
		LB_ASSERT(_mWriteIndex < TSize, "Invalid Address!");
		return &(_mBuffer[_mWriteIndex]);
	}

	template<Size TSize, Size TMaxDataSize>
	Size CAsyncBuffer<TSize, TMaxDataSize>::GetWritableSize() const
	{
		LB_ASSERT(_mWriteIndex < TSize, "Invalid Index!");
		
		int aPassIndex	= _mPassIndex;
		int aReadIndex	= _mReadIndex;
		int aWriteIndex = _mWriteIndex;
		Size aSize = 0;

		if (aPassIndex != -1)
		{
			LB_ASSERT(aWriteIndex <= aPassIndex, "Invalid Index");
			aSize = aPassIndex - aWriteIndex;
		}
		else if (aReadIndex > aWriteIndex)
			aSize = aReadIndex - aWriteIndex;
		else
			aSize = GetUsableSize();

		LB_ASSERT(aSize <= TSize, "Invalid Size!");
		return aSize;
	}
}