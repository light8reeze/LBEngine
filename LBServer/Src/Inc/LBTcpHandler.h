/**
	@file	LBTcpHandler.h
	@brief	LBServer�� TCP ��Ʈ��ũ �̺�Ʈ ó�� ���� ���
	@date	2020-04-06
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBHandler.h"

namespace LBNet
{
	class CGameObject;

	/**
		@brief		TCP ��Ŷ �̺�Ʈ Ÿ�� ����
	*/
	using TCPHandleType = std::function<ErrCode(CPacketHeader*, Size, SharedObject<CGameObject>&)>;
	
	#pragma warning(disable : 4251)
	class LBS_EXPORT CTcpHandler : public CMessageHandler<TCPHandleType>
	{
	private:
		CTcpHandler() = default;

		static CTcpHandler __mSingleton;

	public:
		static CTcpHandler& Instance();
	};
	#pragma warning(default : 4251)
}