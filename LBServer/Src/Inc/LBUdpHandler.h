/**
	@file	LBUdpHandler.h
	@brief	LBServer�� UDP ��Ʈ��ũ �̺�Ʈ ó�� ���� ���
	@date	2020-04-06
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBHandler.h"

namespace LBNet
{
	class CUdpObject;

	/**
		@brief		UDP ��Ŷ �̺�Ʈ Ÿ�� ����
	*/
	using UDPHandleType = std::function<ErrCode(CPacketHeader*, Size, CUdpObject&)>;
	
	#pragma warning(disable : 4251)
	class LBS_EXPORT CUdpHandler : public CMessageHandler<UDPHandleType>
	{
	private:
		CUdpHandler() = default;

		static CUdpHandler __mSingleton;

	public:
		static CUdpHandler& Instance();
	};
	#pragma warning(default : 4251)
}