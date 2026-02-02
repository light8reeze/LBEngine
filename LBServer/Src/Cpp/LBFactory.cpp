#include "LBFactory.h"

namespace LBNet
{
	CFactory CFactory::__mSingleton;

	CFactory::CFactory() : __mPools(), __mIsInitial(false)
	{
	}

	CFactory::~CFactory()
	{
	}

	CFactory& CFactory::Instance()
	{
		return __mSingleton;
	}

	ErrCode CFactory::Initialize()
	{
		LB_ASSERT(__mIsInitial == false, "Error");

		for (auto& aPair : __mPools)
		{
			aPair.second->Initialize();
		}

		__mIsInitial = true;
		return 0;
	}

	ErrCode CFactory::Close()
	{
		__mPools.clear();

		return 0;
	}
}