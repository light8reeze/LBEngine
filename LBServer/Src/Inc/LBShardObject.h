/**
	@file	LBShardObject.h
	@brief	LBServer�� ���� ������Ʈ ���� ���
	@date	2019-10-05
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBServer.h"
#include "LBGameObject.h"

namespace LBNet
{
	/**
		@brief		�л� ������ ���Ǵ� ���� �⺻ ������Ʈ Ŭ����
		@details	�л� ������ �⺻ ������Ʈ�� ����� 1:1����ȴ�.
					�л� ���� ���� ������ ���� ������Ʈ�� ��ӹ޾�
					���ӳ��� ������Ʈ Ŭ������ �����Ѵ�.
		@warning	���� ������Ʈ�� ���� ���� �������� �ʴ´�.
		@date		2019-10-05
		@auther		light8reeze(light8reeze@gmail.com)
	*/
	class CShardObject : public CGameObject
	{
	public:
		CShardObject() {}
		virtual ~CShardObject(){}

	public:
		virtual ErrCode OnConnect() { return 0; }
		virtual void	OnDisconnect() {}
		virtual bool	OnConnectFail(ErrCode /*pErr*/) 
		{
			return true;
		}
	};
}