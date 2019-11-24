/**
	@file	LBTcpClient.h
	@brief	LBClient의 TCP 클라이언트 세션 관련 헤더파일
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
		@brief		TCP 클라이언트 클래스
		@details	Blocking 방식으로 Network IO를 실행한다.
		@warnning	스레드 안전성을 보장하지 않는다.
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