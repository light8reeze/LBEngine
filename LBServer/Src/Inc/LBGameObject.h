/**
	@file	LBGameObject.h
	@brief	LBServer�� �⺻ ������Ʈ ���� ���
	@date	2019-09-07
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBSession.h"

namespace LBNet
{
	/**
		@brief		���ǰ� ����Ǵ� ���� �⺻ ������Ʈ Ŭ����
		@details	������ �⺻ ������Ʈ�� ���ǰ� 1:1����ȴ�.
					���� ���� ������ ���� ������Ʈ�� ��ӹ޾� 
					���ӳ��� ������Ʈ Ŭ������ �����Ѵ�.
		@warning	���ǰ��� ������ ���� Ŭ������ �Լ��� ���ؼ� �������Ѿ� �Ѵ�.
		@date		2019-09-07
		@auther		light8reeze(light8reeze@gmail.com)
	*/
	class LBS_EXPORT CGameObject
	{
	public:
		CGameObject();
		virtual ~CGameObject() {}

	public:
		void LinkSession(SharedObject<CSession>& pSession);
		void Unlink();
		virtual void OnAccept() {}
		virtual void OnDisconnect() {}
		void SetDisconnect();
		ErrCode Send(void* pBuffer, int pSize);
		ErrCode Send(SharedObject<CSender>& pSender);

		const CSessionKey GetSessionKey() const;
		std::string&& GetIPAddress() const;
		unsigned short GetPort() const;

	protected:
		#pragma warning(disable : 4251)
		WeakObject<CSession> _mSession;
		#pragma warning(default : 4251)
	};
}