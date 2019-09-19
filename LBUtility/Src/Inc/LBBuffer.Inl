#include "LBQueue.h"
#include <sstream>
namespace LBNet
{
	/**
		@brief CBuffer의 생성자
	*/
	template<Size TSize>
	CBuffer<TSize>::CBuffer() : _mUseSize(0), _mReadIndex(0), _mWriteIndex(0), _mBuffer()
	{
	}

	template<Size TSize>
	void CBuffer<TSize>::Clear()
	{
		_mReadIndex		= 0;
		_mUseSize		= 0;
		_mWriteIndex	= 0;
		::memset(_mBuffer, 0, TSize);
	}

	template<Size TSize>
	bool CBuffer<TSize>::Push(const char* pData, int pSize)
	{
		LB_ASSERT(pData != nullptr, "Error!");
		LB_ASSERT(pSize > 0,		"Error!");

		Size aDataSize = static_cast<Size>(sizeof(CBufferHeader) + pSize);
		if (aDataSize > GetUsableSize())
			return false;

		reinterpret_cast<CBufferHeader*>(_mBuffer + _mWriteIndex)->mDataSize = pSize;
		::memcpy_s(_mBuffer + _mWriteIndex + sizeof(CBufferHeader), GetUsableSize(), pData, pSize);
		_mUseSize		+= pSize;
		_mWriteIndex	+= pSize;
		return true;
	}

	template<Size TSize>
	char* CBuffer<TSize>::Front(Size& pSize, ErrCode& pErr)
	{
		if (GetUsingSize() < sizeof(CBufferHeader))
			return nullptr;

		char* aData = _mBuffer[_mReadIndex];
		pSize = reinterpret_cast<CBufferHeader*>(aData)->mDataSize;
		aData += sizeof(CBufferHeader);

		if (pSize > TSize - sizeof(CBufferHeader))
			return nullptr;

		_mReadIndex += pSize + sizeof(CBufferHeader);
		return aData;
	}

	template<Size TSize>
	void CBuffer<TSize>::Pop()
	{
		::memmove_s(_mBuffer + _mReadIndex, TSize - _mReadIndex, _mBuffer, TSize);
		_mWriteIndex	-= _mReadIndex;
		_mUseSize		-= _mReadIndex;
		_mReadIndex		= 0;
	}

	template<Size TSize>
	Size CBuffer<TSize>::GetUsingSize() const
	{
		return _mUseSize;
	}

	template<Size TSize>
	Size CBuffer<TSize>::GetUsableSize() const
	{
		return GetBufferSize() - _mUseSize;
	}

	template<Size TSize>
	constexpr Size CBuffer<TSize>::GetBufferSize() const
	{
		static_assert(TSize > 0);
		return TSize;
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