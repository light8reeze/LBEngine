#include "LBTcpClient.h"
#include "LBEncryption.h"

namespace LBNet
{
	CTcpClient::CTcpClient() : __mSocket(), __mBuffer(eSzPacketMax),
		__mState(EState::eDisconnected), __mLastError(0)
	{
		__mBuffer.Clear();
	}

	CTcpClient::CTcpClient(Size pBufSize) : __mSocket(), __mBuffer(pBufSize),
		__mState(EState::eDisconnected), __mLastError(0)
	{
		__mBuffer.Clear();
	}

	ErrCode CTcpClient::Connect(const char* pIp, unsigned short pPort)
	{
		ErrCode aResult = __mSocket.Connect(pIp, pPort);

		if (aResult == 0)
			__mState = EState::eConnected;

		return aResult;
	}

	ErrCode CTcpClient::Receive(bool pIsZeroRecv)
	{
		Size	aSize		= __mBuffer.GetUsableSize();
		char*	aWritePtr	= __mBuffer.GetWritePointer();

		if (aSize < eSzPacketMin || __mBuffer.GetBufferSize() < aSize)
		{
			SetDisconnect(eErrCodeSesBufferFull);
			return eErrCodeSesBufferFull;
		}

		if (pIsZeroRecv)
			aSize = 0;

		int		aReceived = 0;
		ErrCode aErr = __mSocket.Receive(aWritePtr, aSize, aReceived);
		if (aErr != 0)
		{
			SetDisconnect(aErr);
			return aErr;
		}

		if (aSize == 0 && !pIsZeroRecv)
		{
			SetDisconnect(eErrCodeSesDisconnected);
			return eErrCodeSesDisconnected;
		}

		if (!__mBuffer.OnPush(static_cast<Size>(aReceived)))
		{
			SetDisconnect(eErrCodeSesBufferFull);
			return eErrCodeSesBufferFull;
		}

		return 0;
	}

	ErrCode CTcpClient::ProcessPacket()
	{
		if (__mState == EState::eDisconnected)
			return eErrCodeSesDisconnected;

		Size	aSize = 0;
		ErrCode aResult = 0;
		char*	aData = __mBuffer.Front(aSize, aResult);

		LB_ASSERT(aSize >= sizeof(CPacketHeader), "Packet Error!");

		if (aData != nullptr)
		{
			Size aEncryptHdSize = 0;
			if (CEncryptor::Instance() != nullptr)
			{
				aEncryptHdSize = CEncryptor::Instance()->GetHeaderSize();
				aSize -= aEncryptHdSize;
				aResult = CEncryptor::Instance()->Decrypt(aData, aSize);

				if (aResult != 0)
				{
					SetDisconnect(aResult);
					return aResult;
				}
			}

			CPacketHeader* aHeader = reinterpret_cast<CPacketHeader*>(aData + aEncryptHdSize);
			aResult = CClientHandler::Instance().Process(aHeader->mMessage, aHeader, aSize);
		}

		if (aResult != 0)
		{
			SetDisconnect(aResult);
			return aResult;
		}

		return 0;
	}

	ErrCode CTcpClient::Send(void* pBuffer, int pSize)
	{
		int		aSendSize = 0;
		ErrCode aResult = __mSocket.Send(pBuffer, pSize, aSendSize);

		if (aResult != 0 || aSendSize == 0)
		{
			SetDisconnect(aResult);
		}

		return aResult;
	}

	ErrCode CTcpClient::Send(SharedObject<CSender>& pSender)
	{
		if (pSender == nullptr)
			return eErrCodeNullSender;

		LB_ASSERT(__mState == EState::eConnected, "Invalid!");

		auto aSendPtr = pSender->GetSendPointer();
		auto aSendSize = pSender->GetSendSize();
		int aSendedSize = 0;

		if (aSendPtr == nullptr)
			return eErrCodeNullSender;

		ErrCode aResult = __mSocket.Send(aSendPtr, aSendSize, aSendedSize);
		if (aResult != 0 || aSendedSize == 0)
			SetDisconnect(aResult);

		return aResult;
	}

	ErrCode CTcpClient::Close()
	{
		if (__mState == EState::eDisconnected)
			return 0;

		return __mSocket.Close();
	}

	ErrCode CTcpClient::SetDisconnect(ErrCode pErr)
	{
		__mLastError = pErr;
		return Close();
	}

	CTcpClient::EState CTcpClient::GetState() const
	{
		return __mState;
	}

	ErrCode CTcpClient::GetLastError() const
	{
		return __mLastError;
	}
}