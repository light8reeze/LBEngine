/**
	@file	LBClientHandler.h
	@brief	LBClient�� Ŭ���̾�Ʈ ��Ŷó�� ���� �������
	@date	2019-11-24
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBClient.h"
#include "LBHandler.h"

namespace LBNet
{
	/**
		@brief	Ŭ���̾�Ʈ ��Ŷ ó�� Ŭ���� Ÿ�� ����
	*/
	using PacketHandle	= std::function<ErrCode(CPacketHeader*, Size)>;
	
	#pragma warning(disable : 4251)
	class LBC_EXPORT CClientHandler : public CMessageHandler<PacketHandle>
	{
	private:
		CClientHandler() = default;

		static CClientHandler __mSingleton;

	public:
		static CClientHandler& Instance();
	};
	#pragma warning(default : 4251)
}