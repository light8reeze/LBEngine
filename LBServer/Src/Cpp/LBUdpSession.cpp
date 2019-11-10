#include "LBUdpSession.h"
#include "LBHandler.h"
#include "LBUdpObject.h"
#include "LBEncyption.h"

namespace LBNet
{
	CUdpSession CUdpSession::__mSingleton;

	CUdpSession::CUdpSession() : __mSocket(), __mBuffer(eSzPacketMax)
	{
		__mBuffer.Clear();
	}

	CUdpSession::~CUdpSession()
	{
	}

	ErrCode CUdpSession::ReceiveFrom()
	{
		Size aSize		= __mBuffer.GetUsableSize();
		char* aWritePtr = __mBuffer.GetWritePointer();

		__mSocket.ReceiveFromAsync(aWritePtr, aSize, __mEndPoint,
			[this](const boost::system::error_code& pError, std::size_t pRecvSize)
		{
			if (pError.value() != 0 || pRecvSize == 0)
			{
				return;
			}

			ErrCode aErr = OnReceiveFrom(static_cast<Size>(pRecvSize));

			aErr = ReceiveFrom();
		});

		return 0;
	}

	ErrCode CUdpSession::OnReceiveFrom(Size pSize)
	{
		if (pSize == 0)
			return eErrCodeInvalidSize;

		if (!__mBuffer.OnPush(pSize))
		{
			__mBuffer.Clear();
			return eErrCodeSesBufferFull;
		}

		Size	aSize = 0;
		ErrCode aResult = 0;
		char*	aData = __mBuffer.Front(aSize, aResult);
		CUdpObject aUdpObject(__mEndPoint);

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
					return aResult;
				}
			}

			CPacketHeader* aHeader = reinterpret_cast<CPacketHeader*>(aData + aEncryptHdSize);
			aResult = CMessageHandler::Process(aHeader->mCommand, aHeader, aSize, aUdpObject);
		}

		if (aResult != 0)
		{
			return aResult;
		}

		return 0;
	}

	ErrCode CUdpSession::SendTo(void* pBuffer, int pSize, CUdpObject& pObject)
	{
		__mSocket.SendToAsync(pBuffer, pSize, pObject.GetEndPoint(),
			[this](const boost::system::error_code& /*pError*/, std::size_t /*pSendSize*/)
		{
		});

		return 0;
	}

	ErrCode CUdpSession::SendTo(SharedObject<CSender> pSender, CUdpObject& pObject)
	{
		auto aSendPtr = pSender->GetSendPointer();
		auto aSendSize = pSender->GetSendSize();

		if (aSendPtr == nullptr)
			return eErrCodeNullSender;

		__mSocket.SendToAsync(aSendPtr, aSendSize, pObject.GetEndPoint(),
			[this, pSender](const boost::system::error_code& /*pError*/, std::size_t /*pSendSize*/)
		{
		});

		return 0;
	}

	CUdpSession& CUdpSession::Instance()
	{
		return __mSingleton;
	}
}