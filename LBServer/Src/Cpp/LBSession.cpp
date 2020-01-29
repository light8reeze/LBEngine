#include "LBSession.h"
#include "LBGameObject.h"
#include "LBFactory.h"
#include "LBEncryption.h"
#include "LBTimer.h"
#include "LBLogger.h"

namespace LBNet
{
	int CSession::_mSesCnt = 0;

	CTcpHandler CTcpHandler::__mSingleton;

	CTcpHandler& CTcpHandler::Instance()
	{
		return __mSingleton;
	}

	CSession::CSession() : _mSocket(), __mBuffer(eSzPacketMax),
		_mState(EState::eClosed), _mMutex(), _mLastError(0)
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
		LB_ASSERT(_mState == EState::eClosed,	"Invalid!");
		LB_ASSERT(__mGameObject != nullptr,			"Invalid!");

		__mBuffer.Clear();
		_mState = EState::eStable;
		__mGameObject->OnAccept();
		_mSocket.SetReuse(true);
		_mLastError = 0;
		
		{
			WriteLock aLocker(_mMutex);
			++_mSesCnt;
		}

		CConsoleLog(ELogType::eLogInfo) << "On Accept Ses Cnt : " << _mSesCnt;
		return Receive();
	}

	ErrCode CSession::Receive()
	{
		LB_ASSERT(__mGameObject != nullptr, "Object Not Linked to Session");

		Size	aSize		= __mBuffer.GetUsableSize();
		char*	aWritePtr	= __mBuffer.GetWritePointer();

		if (_mState != EState::eStable)
		{
			return eErrCodeSesDisconnected;
		}

		// ���۰� ���� á������ ������ �����Ѵ�.
		if (aSize < eSzPacketMin || __mBuffer.GetBufferSize() < aSize)
		{
			SetDisconnect(eErrCodeSesBufferFull);
			return eErrCodeSesBufferFull;
		}

		auto aSharedSession = GetShared();
		_mSocket.ReceiveAsync(aWritePtr, aSize,
			[this, aSharedSession](const boost::system::error_code& pError, std::size_t pRecvSize)
		{
			if (pError.value() != 0 || pRecvSize == 0)
			{
				SetDisconnect();
				return;
			}

			ErrCode aErr = OnReceive(static_cast<Size>(pRecvSize));
			if (aErr != 0)
			{
				SetDisconnect(aErr);
				return;
			}

			if(_mState == EState::eStable)
				Receive();
		});

		return 0;
	}

	ErrCode CSession::OnReceive(Size pSize)
	{
		LB_ASSERT(_mState == EState::eStable, "Invalid!");

		if (pSize == 0)
			return eErrCodeInvalidSize;

		if (_mState != EState::eStable)
			return eErrCodeSesDisconnected;

		if (!__mBuffer.OnPush(pSize))
			return eErrCodeSesBufferFull;

		Size	aSize = 0;
		ErrCode aResult = 0;
		char*	aData = __mBuffer.Front(aSize, aResult);
		auto	aGameObject = GetGameObject<CGameObject>();

		while(aData != nullptr && aGameObject != nullptr && aResult == 0)
		{
			Size aEncryptHdSize = 0;
			if (CEncryptor::Instance() != nullptr)
			{
				aEncryptHdSize = CEncryptor::Instance()->GetHeaderSize();
				aSize -= aEncryptHdSize;
				aResult = CEncryptor::Instance()->Decrypt(aData, aSize);

				if (aResult != 0)
					return aResult;
			}

			CPacketHeader* aHeader = reinterpret_cast<CPacketHeader*>(aData + aEncryptHdSize);
			aResult = CTcpHandler::Instance().Process(aHeader->mMessage, aHeader, aSize, aGameObject);
			if (aResult != 0)
				break;

			aData	= __mBuffer.Front(aSize, aResult);
		}

		if (aResult != 0)
			return aResult;

		__mBuffer.Pop();
		return 0;
	}

	ErrCode CSession::Send(void* pBuffer, int pSize)
	{
		{
			ReadLock aLocker(_mMutex);
			if (_mState != EState::eStable)
			{
				return 0;
			}
		}

		auto aSharedSession = GetShared();
		_mSocket.SendAsync(pBuffer, pSize,
			[this, aSharedSession](const boost::system::error_code& pError, std::size_t pSendSize)
		{
			if (pError.value() != 0 || pSendSize == 0)
				SetDisconnect();
		});

		return 0;
	}

	ErrCode CSession::Send(SharedObject<CSender> pSender)
	{
		if (pSender == nullptr)
			return eErrCodeNullSender;

		auto aSendPtr = pSender->GetSendPointer();
		auto aSendSize = pSender->GetSendSize();

		if (aSendPtr == nullptr)
			return eErrCodeNullSender;

		{
			ReadLock aLocker(_mMutex);
			if (_mState == EState::eDisconnect)
			{
				return 0;
			}
		}

		auto aSharedSession = GetShared();

		_mSocket.SendAsync(aSendPtr, aSendSize,
			[this, pSender, aSharedSession](const boost::system::error_code& pError, std::size_t pSendSize)
		{
			if (pError.value() != 0 || pSendSize == 0)
				SetDisconnect();
		});

		return 0;
	}

	ErrCode CSession::Close()
	{
		{
			ReadLock aLocker(_mMutex);

			if (_mState == EState::eClosed)
				return 0;
		}

		{
			WriteLock aLocker(_mMutex);
			
			_mState = EState::eClosed;
			__mBuffer.Clear();
			--_mSesCnt;
		}
		CConsoleLog(ELogType::eLogInfo) << "On Close Ses Cnt : " << _mSesCnt << " Last Error : " << _mLastError;

		return 0;
	}

	ErrCode CSession::SetDisconnect(ErrCode pError)
	{
		LB_ASSERT(_mLastError == 0, "Error!");
		{
			WriteLock aLock(_mMutex);

			if (_mState == EState::eStable)
			{
				_mSocket.Close();
				_mState = EState::eDisconnect;

				CTimer::Start(1s, [aObserver = std::move(WeakObject<CSession>(__mInstance))](ErrCode pErr)
				{
					if (pErr == 0 && !aObserver.expired())
					{
						CConsoleLog(ELogType::eLogInfo) << "Dangling!!";
					}
				});

				__mInstance = nullptr;
				_mLastError = pError;

				RemoveObject();
			}
		}

		return 0;
	}

	const CTcpSocket::EndPointType& CSession::GetEndPoint() const
	{
		return _mSocket.GetEndPoint();
	}

	void CSession::SetShared(SharedObject<CSession> pShared)
	{
		__mInstance = pShared;
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

	SharedObject<CSession> CSession::GetShared()
	{
		return __mInstance;
	}

	bool CSession::Delete(CSession* pObject)
	{
		if (pObject == nullptr)
			return false;

		pObject->Close();

		return CFactory::Instance().Delete(pObject);
	}
}