#include "LBSession.h"
#include "LBHandler.h"

namespace LBNet
{
	CSession::CSession() : __mSocket(), __mBuffer(), 
		__mState(EState::eDisconnect), __mLocker()
	{
	}

	CSession::~CSession()
	{
		Close();
	}

	ErrCode CSession::Initialize()
	{
		__mBuffer.Clear();
	}

	ErrCode CSession::OnAccept()
	{
		LB_ASSERT(__mState == EState::eDisconnect, "Invalid!");

		__mState = EState::eStable;
		return Receive();
	}

	ErrCode CSession::Receive()
	{
		Size	aSize = __mBuffer.GetWritableSize();
		char*	aWritePtr = __mBuffer.GetWriteAddress();

		if (__mState == EState::eDisconnect)
		{
			return 2;
		}

		// 버퍼가 가득 찼을때는 접속을 해제한다.
		if (aSize < eSzPacketMin)
		{
			Close();
			return 1;
		}

		__mSocket.ReceiveAsync(aWritePtr, aSize,
			[this](const boost::system::error_code& pError, std::size_t pRecvSize)
		{
			OnReceive(pRecvSize);
			Receive();
		});
	}

	ErrCode CSession::OnReceive(int pSize)
	{
		LB_ASSERT(__mState == EState::eStable, "Invalid!");

		if (pSize == 0)
			return 1;

		if (__mState == EState::eDisconnect)
			return 2;

		__mBuffer.OnPush(pSize);
		Size	aSize = 0;
		char*	aData = __mBuffer.Pop(aSize);
		ErrCode aResult = 0;
		auto aManaged = CManagedObject::MakeManaged(*this);
		auto aGameObject = GetGameObject<CGameObject>();

		LB_ASSERT(aSize > 0, "Packet Error!");

		if (aData != nullptr)
		{
			CPacketHeader* aHeader = reinterpret_cast<CPacketHeader*>(aData);
			aResult = CMessageHandler::Process(aHeader->mCommand, aHeader, aSize, (*aManaged), aGameObject);
		}

		if (aResult != 0)
		{
			Close();
			return aResult;
		}

		return 0;
	}

	ErrCode CSession::Send(void* pBuffer, int pSize)
	{
		LB_ASSERT(__mState == EState::eStable,	"Invalid!");\

		__mSocket.SendAsync(pBuffer, pSize,
			[this](const boost::system::error_code& pError, std::size_t pRecvSize)
		{
			if (pError.value() != 0)
				Close();
		});
	}

	ErrCode CSession::Close()
	{
		LB_ASSERT(__mState == EState::eDisconnect,	"Invalid!");

		{
			CLocker::AutoLock aLocker(__mLocker);

			__mSocket.Close();
			__mBuffer.Clear();
			__mState = EState::eDisconnect;
		}
	}

	ErrCode CSession::SetDisconnect()
	{
		SetReturn();
		return 0;
	}

	void CSession::RemoveObject()
	{
		__mGameObject = std::move(SharedObject<CGameObject>());
	}

	ErrCode CSession::_OnDelete()
	{
		Close();
	}
}