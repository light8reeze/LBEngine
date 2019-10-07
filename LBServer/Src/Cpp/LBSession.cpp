#include "LBSession.h"
#include "LBHandler.h"
#include "LBGameObject.h"
#include "LBSessionManager.h"
#include <iostream> //@test

namespace LBNet
{
	CSession::CSession() : _mSocket(), __mBuffer(), 
		__mState(EState::eDisconnect), _mMutex()
	{
	}

	CSession::~CSession()
	{
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

		__mBuffer.Clear();
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
			if (pError.value() != 0 || pRecvSize == 0)
			{
				SetDisconnect();
				OnAccessEnd();
				return;
			}

			ErrCode aErr = OnReceive(static_cast<Size>(pRecvSize));
			OnAccessEnd();
			if (aErr != 0)
			{
				SetDisconnect();
			}

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
		auto aGameObject = GetGameObject<CGameObject>();

		LB_ASSERT(aSize > 0, "Packet Error!");

		if (aData != nullptr)
		{
			CPacketHeader* aHeader = reinterpret_cast<CPacketHeader*>(aData);
			aResult = CMessageHandler::Process(aHeader->mCommand, aHeader, aSize, aGameObject);
		}

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

		WriteLock aLocker(_mMutex);

		__mBuffer.Clear();
		++(_mSessionKey.mField.mReuse);

		if (__mGameObject != nullptr)
		{
			__mGameObject->OnDisconnect();
			__mGameObject->Unlink();
		}

		return 0;
	}

	ErrCode CSession::SetDisconnect()
	{
		WriteLock aLock(_mMutex);

		if (__mState != EState::eDisconnect)
		{
			_mSocket.Close();
			__mState = EState::eDisconnect;
			std::cout << _mSessionKey.mKey << "Set DisConnected!" << std::endl; //@test
		}

		SetReturn();
		return 0;
	}

	void CSession::SetSessionKey(CSessionKey& pObjKey)
	{
		_mSessionKey = pObjKey;
	}

	const CSessionKey& CSession::GetSessionKey() const
	{
		return _mSessionKey;
	}

	CSessionKey CSession::GetSessionKey()
	{
		return _mSessionKey;
	}

	void CSession::RemoveObject()
	{
		__mGameObject = std::move(SharedObject<CGameObject>());
	}

	void CSession::OnDelete()
	{
		Close();
		CSessionManager::Instance().ReturnKey(_mSessionKey);

		__super::OnDelete();
	}
}