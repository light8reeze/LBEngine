/**
	@file	LBGameObject.h
	@brief	LBServer�� �⺻ ������Ʈ ���� ���
	@date	2019-09-07
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBServer.h"
#include "LBSession.h"
#include "LBLocker.h"
#include <queue>

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

		const CSessionKey GetSessionKey() const;

	protected:
		WeakObject<CSession> _mSession;
	};
}