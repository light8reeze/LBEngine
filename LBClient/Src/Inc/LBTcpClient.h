/**
	@file	LBTcpClient.h
	@brief	LBClient�� TCP Ŭ���̾�Ʈ ���� ���� �������
	@date	2019-11-24
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBClient.h"
#include "LBSocket.h"
#include "LBBuffer.h"
#include "LBSender.h"
#include "LBClientHandler.h"

namespace LBNet
{
	/**
		@brief		TCP Ŭ���̾�Ʈ Ŭ����
		@details	Blocking ������� Network IO�� �����Ѵ�.
		@warnning	������ �������� �������� �ʴ´�.
		@date		2019-11-24
		@auther		light8reeze(light8reeze@gmail.com)
	*/
	class LBC_EXPORT CTcpClient
	{
	private:
		enum class EState
		{
			eConnected,
			eDisconnected
		};
	public:
		CTcpClient();
		CTcpClient(Size pBufSize);
		~CTcpClient() = default;

		CTcpClient(const CTcpClient&) = delete;
		CTcpClient& operator=(const CTcpClient&) = delete;

		ErrCode Connect(const char* pIp, unsigned short pPort);
		ErrCode Receive(bool pIsZeroRecv = false);
		ErrCode ProcessPacket();
		ErrCode Send(void* pBuffer, int pSize);
		ErrCode Send(SharedObject<CSender>& pSender);
		ErrCode Close();
		ErrCode SetDisconnect(ErrCode pErr = 0);

		EState	GetState() const;
		ErrCode GetLastError() const;

	private:
		CTcpSocket	__mSocket;
		CBuffer		__mBuffer;
		EState		__mState;
		ErrCode		__mLastError;
	};
}