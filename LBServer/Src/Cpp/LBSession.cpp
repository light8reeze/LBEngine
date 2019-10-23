#include "LBSession.h"
#include "LBHandler.h"
#include "LBGameObject.h"
#include "LBSessionManager.h"
#include "LBEncyption.h"

namespace LBNet
{
	CSession::CSession() : _mSocket(), __mBuffer(eSzPacketMax),
		_mState(EState::eDisconnect), _mMutex()
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
		LB_ASSERT(_mState == EState::eDisconnect,	"Invalid!");
		LB_ASSERT(__mGameObject != nullptr,			"Invalid!");

		__mBuffer.Clear();
		_mState = EState::eStable;
		__mGameObject->OnAccept();
		_mSocket.SetReuse(true);
		return Receive();
	}

	ErrCode CSession::Receive()
	{
		LB_ASSERT(__mGameObject != nullptr, "Object Not Linked to Session");

		Size	aSize = __mBuffer.GetUsableSize();
		char*	aWritePtr = __mBuffer.GetWritePointer();

		if (!OnAccess())
		{
			return 0;
		}

		if (_mState == EState::eDisconnect)
		{
			return eErrCodeSesDisconnected;
		}

		// 버퍼가 가득 찼을때는 접속을 해제한다.
		if (aSize < eSzPacketMin)
		{
			SetDisconnect();
			OnAccessEnd();
			return eErrCodeSesBufferFull;
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
			if (aErr != 0)
			{
				SetDisconnect();
				OnAccessEnd();
				return;
			}

			OnAccessEnd();
			if(GetState() == CManagedObject::EState::eUsing)
				Receive();
		});

		return 0;
	}

	ErrCode CSession::OnReceive(Size pSize)
	{
		LB_ASSERT(_mState == EState::eStable, "Invalid!");

		if (pSize == 0)
			return eErrCodeInvalidSize;

		if (_mState == EState::eDisconnect)
			return eErrCodeSesDisconnected;

		if (!__mBuffer.OnPush(pSize))
		{
			SetDisconnect();
			return eErrCodeSesBufferFull;
		}

		Size	aSize = 0;
		ErrCode aResult = 0;
		char*	aData = __mBuffer.Front(aSize, aResult);
		auto aGameObject = GetGameObject<CGameObject>();

		LB_ASSERT(aSize >= sizeof(CPacketHeader), "Packet Error!");

		if (aData != nullptr && aGameObject != nullptr)
		{
			Size aEncryptHdSize = 0;
			if (CEncryptor::Instance() != nullptr)
			{
				aEncryptHdSize = CEncryptor::Instance()->GetHeaderSize();
				aSize -= aEncryptHdSize;
				aResult = CEncryptor::Instance()->Decypt(aData, aSize);

				if (aResult != 0)
				{
					SetDisconnect();
					return aResult;
				}
			}

			CPacketHeader* aHeader = reinterpret_cast<CPacketHeader*>(aData + aEncryptHdSize);
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
		LB_ASSERT(_mState == EState::eStable,	"Invalid!");

		if (!OnAccess())
		{
			return 0;
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

	ErrCode CSession::Send(SharedObject<CSender> pSender)
	{
		if (pSender == nullptr)
			return eErrCodeNullSender;

		LB_ASSERT(_mState == EState::eStable, "Invalid!");

		auto aSendPtr = pSender->GetSendPointer();
		auto aSendSize = pSender->GetSendSize();

		if (aSendPtr == nullptr)
			return eErrCodeNullSender;

		if (!OnAccess())
			return 0;

		_mSocket.SendAsync(aSendPtr, aSendSize,
			[this, pSender](const boost::system::error_code& pError, std::size_t pSendSize)
		{
			if (pError.value() != 0 || pSendSize == 0)
				SetDisconnect();

			OnAccessEnd();
		});

		return 0;
	}

	ErrCode CSession::Close()
	{
		LB_ASSERT(_mState == EState::eDisconnect,	"Invalid!");

		WriteLock aLocker(_mMutex);

		__mBuffer.Clear();
		++(_mSessionKey.mField.mReuse);

		return 0;
	}

	ErrCode CSession::SetDisconnect()
	{
		WriteLock aLock(_mMutex);

		if (_mState != EState::eDisconnect)
		{
			_mSocket.Close();
			_mState = EState::eDisconnect;

			RemoveObject();
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
		if (__mGameObject != nullptr)
		{
			__mGameObject->OnDisconnect();
			__mGameObject->Unlink();
			__mGameObject = nullptr;
		}
	}

	void CSession::OnDelete()
	{
		Close();
		CSessionManager::Instance().ReturnKey(_mSessionKey);

		__super::OnDelete();
	}
}