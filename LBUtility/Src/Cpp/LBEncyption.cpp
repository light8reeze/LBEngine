#include "LBEncyption.h"

namespace LBNet
{
	CEncryptor* CEncryptor::__mSingleton = nullptr;

	CEncryptor::CEncryptor() : _mHeaderSize(0)
	{
		LB_ASSERT(__mSingleton == nullptr, "Invalid!");
		__mSingleton = this;
	}

	CEncryptor::~CEncryptor()
	{
	}

	Size CEncryptor::GetHeaderSize()
	{
		LB_ASSERT(_mHeaderSize > 0, "Invalid Header Size!");
		return _mHeaderSize;
	}

	CEncryptor* CEncryptor::Instance()
	{
		return __mSingleton;
	}
}