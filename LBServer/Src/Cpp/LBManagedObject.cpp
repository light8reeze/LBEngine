#include "LBManagedObject.h"

namespace LBNet
{
	CManagedObject::CManagedObject() : __mRefCnt(0), __mObjState(EState::eUsing)
	{
	}

	bool CManagedObject::OnAccess()
	{
		LB_ASSERT(__mObjState != EState::eReturned, "Error!");

		if (__mObjState == EState::eUsing)
		{
			++__mRefCnt;
			return true;
		}

		return false;
	}

	void CManagedObject::OnAccessEnd()
	{
		LB_ASSERT(__mObjState != EState::eReturned, "Error!");

		if (__mRefCnt > 0)
		{
			--__mRefCnt;

			if (__mObjState == EState::eReturnWait)
			{
				__mObjState = EState::eReturned;
				_OnDelete();
			}
		}
	}

	ErrCode CManagedObject::SetReturn()
	{
		LB_ASSERT(__mObjState != EState::eReturned, "Error!");

		__mObjState = EState::eReturnWait;
		return 0;
	}

	CManagedObject::EState CManagedObject::GetState()
	{
		return __mObjState;
	}

	Size CManagedObject::GetRefCnt()
	{
		return __mRefCnt;
	}

	ErrCode CManagedObject::_OnDelete()
	{
		return 0;
	}
}