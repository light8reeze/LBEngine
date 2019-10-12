/**
	@file	LBShard.h
	@brief	LBServer�� ���� ���� ���
	@date	2019-09-22
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBShardObject.h"

namespace LBNet
{
	/**
		@brief		TCP ���� Ŭ����
		@details	�л꼭�� ���ῡ ���ȴ�.
		@warning	1.Connect�� ��ϵǴ� �ڵ鷯���� GameObject���� �ڵ尡 �ݵ�� ���� �Ѵ�.
					CSession::SetGameObject�� �ݵ�� ȣ���ؾ� �Ѵ�.
					2.Connect�� ��ϵǴ� �ڵ鷯�� ErrCode(void) ���� �Լ��̴�.
		@date		2019-09-22
		@auther		light8reeze(light8reeze@gmail.com)
	*/
	template<typename TShardObject>
	class CShard : public CSession
	{
	public:
		CShard();
		~CShard() = default;

		virtual ErrCode Initialize() override;
		ErrCode			Connect();
		virtual ErrCode SetDisconnect() override;

		void				SetAddress(const char* pIp, unsigned short pPort);
		void				SetServerNo(unsigned short pServerNo);
		unsigned short		GetServerNo() const;
		virtual void		OnDelete() override;

	private:
		void __OnConnectFail(ErrCode pErr);

	private:
		unsigned short	__mServerNo;
		std::string		__mIp;
		unsigned short	__mPort;
		bool			__mNextConnect;
	};
}

#include "LBShard.Inl"