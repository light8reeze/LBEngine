/**
	@file	LBGameObject.h
	@brief	LBServer�� �⺻ ������Ʈ ���� ���
	@date	2019-09-07
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBServer.h"
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
		virtual ~CGameObject() = 0;

	public:
		void LinkSession(SharedObject<CSession>& pSession);
		void Unlink();

	protected:
		WeakObject<CSession> _mSession;
	};
}