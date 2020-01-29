#include "LBBuffer.h"

namespace LBNet
{
	/**
		@brief CBuffer의 생성자
	*/
	CBuffer::CBuffer(Size pSize) : _mMAX_SIZE(pSize), _mUseSize(0), 
		_mReadIndex(0), _mWriteIndex(0), _mBuffer(nullptr)
	{
		_mBuffer = new char[_mMAX_SIZE];
		::memset(_mBuffer, 0, _mMAX_SIZE);
	}

	CBuffer::~CBuffer()
	{
		delete[] _mBuffer;
	}

	bool CBuffer::Push(const char* pData, Size pSize)
	{
		LB_ASSERT(pData != nullptr, "Error!");
		LB_ASSERT(pSize > 0,		"Error!");

		Size aDataSize = static_cast<Size>(sizeof(CBufferHeader)) + pSize;
		if (aDataSize > GetUsableSize())
			return false;

		reinterpret_cast<CBufferHeader*>(_mBuffer + _mWriteIndex)->mDataSize = pSize;
		::memcpy_s(_mBuffer + _mWriteIndex + sizeof(CBufferHeader), GetUsableSize() - sizeof(CBufferHeader), pData, pSize);
		_mUseSize		+= pSize + sizeof(CBufferHeader);
		_mWriteIndex	+= static_cast<int>(pSize) + sizeof(CBufferHeader);
		return true;
	}

	char* CBuffer::Front(Size& pSize, ErrCode& pErr)
	{
		if (static_cast<int>(_mUseSize) - _mReadIndex < static_cast<int>(sizeof(CBufferHeader)))
			return nullptr;

		pErr = 0;
		char* aData = _mBuffer + _mReadIndex;
		pSize = reinterpret_cast<CBufferHeader*>(aData)->mDataSize;
		aData += sizeof(CBufferHeader);

		// 패킷 버퍼가 가득찬 경우
		// 이러한 경우 연결을 종료한다.
		if (pSize > _mMAX_SIZE - sizeof(CBufferHeader))
		{
			pErr = 1;
			return nullptr;
		}

		if (pSize > _mUseSize - static_cast<Size>(_mReadIndex) + sizeof(CBufferHeader))
			return nullptr;

		// 잘못된 패킷을 받을 경우 사이즈가 비정상으로 들어온다.
		// 이러한 경우 연결을 종료한다.
		if (pSize > _mUseSize)
		{
			pErr = 2;
			return nullptr;
		}

		_mReadIndex += (static_cast<int>(pSize) + static_cast<int>(sizeof(CBufferHeader)));
		return aData;
	}

	void CBuffer::Pop()
	{
		LB_ASSERT(_mUseSize >= static_cast<Size>(_mReadIndex), "Error!");

		::memmove_s(_mBuffer, _mMAX_SIZE, _mBuffer + _mReadIndex, _mMAX_SIZE - _mReadIndex);
		_mWriteIndex	-= _mReadIndex;
		_mUseSize		-= static_cast<Size>(_mReadIndex);
		_mReadIndex		= 0;
	}

	void CBuffer::Clear()
	{
		_mReadIndex = 0;
		_mUseSize = 0;
		_mWriteIndex = 0;
	}

	bool CBuffer::OnPush(Size pSize)
	{
		LB_ASSERT(pSize >= sizeof(CBufferHeader),	"Invalid Enqueue!");
		LB_ASSERT(GetUsableSize() >= pSize,			"Invalid Size!");
		LB_ASSERT(_mReadIndex == 0,					"Invalid Idx!");
		
		if (_mWriteIndex + pSize > _mMAX_SIZE)
			return false;

		_mWriteIndex	+= static_cast<int>(pSize);
		_mUseSize		+= pSize;

		return true;
	}

	char* CBuffer::GetWritePointer()
	{
		LB_ASSERT(_mWriteIndex < _mMAX_SIZE, "Invalid Address!");
		return &(_mBuffer[_mWriteIndex]);
	}

	Size CBuffer::GetUsingSize() const
	{
		return _mUseSize;
	}

	Size CBuffer::GetUsableSize() const
	{
		return _mMAX_SIZE - _mUseSize;
	}

	Size CBuffer::GetBufferSize()
	{
		return _mMAX_SIZE;
	}

}