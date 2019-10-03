#include "LBSession.h"
#include "LBHandler.h"
#include "LBGameObject.h"

namespace LBNet
{
	CSession::CSession() : _mSocket(), __mBuffer(), 
		__mState(EState::eDisconnect), __mLocker(), CManagedObject(), __mGameObject()
	{
	}

	CSession::~CSession()
	{
		Close();
	}

	ErrCode CSession::Initialize()
	{
		__mBuffer.Clear();
		return 0;
	}

	ErrCode CSession::OnAccept()
	{
		LB_ASSERT(__mState == EState::eDisconnect,	"Invalid!");
		LB_ASSERT(__mGameObject != nullptr,			"Invalid!");

		__mState = EState::eStable;
		__mGameObject->OnAccept();
		return Receive();
	}

	ErrCode CSession::Receive()
	{
		LB_ASSERT(__mGameObject != nullptr, "Object Not Linked to Session");

		Size	aSize = __mBuffer.GetUsableSize();
		char*	aWritePtr = __mBuffer.GetWriteAddress();

		if (!OnAccess())
		{
			return 3;
		}

		if (__mState == EState::eDisconnect)
		{
			return 2;
		}

		// 버퍼가 가득 찼을때는 접속을 해제한다.
		if (aSize < eSzPacketMin)
		{
			SetDisconnect();
			return 1;
		}

		_mSocket.ReceiveAsync(aWritePtr, aSize,
			[this](const boost::system::error_code& pError, std::size_t pRecvSize)
		{
			if (pError.value() != 0)
			{
				SetDisconnect();
				return;
			}

			OnReceive(static_cast<Size>(pRecvSize));
			Receive();
		});

		return 0;
	}

	ErrCode CSession::OnReceive(Size pSize)
	{
		LB_ASSERT(__mState == EState::eStable, "Invalid!");

		if (pSize == 0)
			return 1;

		if (__mState == EState::eDisconnect)
			return 2;

		__mBuffer.OnPush(pSize);
		Size	aSize = 0;
		ErrCode aResult = 0;
		char*	aData = __mBuffer.Front(aSize, aResult);
		auto aManaged = CManagedObject::MakeManaged(*this);
		auto aGameObject = GetGameObject<CGameObject>();

		LB_ASSERT(aSize > 0, "Packet Error!");

		if (aData != nullptr)
		{
			CPacketHeader* aHeader = reinterpret_cast<CPacketHeader*>(aData);
			aResult = CMessageHandler::Process(aHeader->mCommand, aHeader, aSize, aGameObject);
		}

		OnAccessEnd();

		if (aResult != 0)
		{
			SetDisconnect();
			return aResult;
		}

		return 0;
	}

	ErrCode CSession::Send(void* pBuffer, int pSize)
	{
		LB_ASSERT(__mState == EState::eStable,	"Invalid!");

		if (!OnAccess())
		{
			return 1;
		}

		_mSocket.SendAsync(pBuffer, pSize,
			[this](const boost::system::error_code& pError, std::size_t pSendSize)
		{
			if (pError.value() != 0 || pSendSize == 0)
				SetDisconnect();

			OnAccessEnd();
		});

		return 0;
	}

	ErrCode CSession::Close()
	{
		LB_ASSERT(__mState == EState::eDisconnect,	"Invalid!");

		{
			CLocker::AutoLock aLocker(__mLocker);

			if (__mState == EState::eStable)
				_mSocket.Close();

			__mBuffer.Clear();
			__mState = EState::eDisconnect;
			++(__mSessionKey.mField.mReuse);

			if(__mGameObject != nullptr)
				__mGameObject->Unlink();
		}

		return 0;
	}

	ErrCode CSession::SetDisconnect()
	{
		SetReturn();
		return 0;
	}

	void CSession::SetSessionKey(CSessionKey& pObjKey)
	{
		__mSessionKey = pObjKey;
	}

	const CSessionKey& CSession::GetSessionKey() const
	{
		return __mSessionKey;
	}

	CSessionKey CSession::GetSessionKey()
	{
		return __mSessionKey;
	}

	void CSession::RemoveObject()
	{
		__mGameObject = std::move(SharedObject<CGameObject>());
	}

	void CSession::OnDelete()
	{
		Close();
		CSessionManager::Instance().ReturnKey(__mSessionKey);
	}
}