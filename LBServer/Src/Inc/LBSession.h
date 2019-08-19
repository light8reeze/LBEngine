/**
	@file	LBSession.h
	@brief	LBServer�� ��Ʈ��ũ ���� ���� ���
	@date	2019-08-19
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBServer.h"
#include "LBSocket.h"
#include "LBBuffer.h"

namespace LBNet
{
	/**
		@brief	TCP ���� Ŭ����
		@date	2019-08-19
		@auther	light8reeze(light8reeze@gmail.com)
	*/
	class LBS_EXPORT CSession
	{
	private:
		using BufferType = CAsyncBuffer<eSzPacketBuffer, eSzPacketMax>;

	public:
		CSession();
		~CSession();



	private:
		CTCPSocket	__mSocket;
		BufferType	__mBuffer;
	};
}