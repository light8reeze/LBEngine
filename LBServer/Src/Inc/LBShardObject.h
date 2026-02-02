/**
	@file	LBShardObject.h
	@brief	LBServer의 샤드 오브젝트 관련 헤더
	@date	2019-10-05
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBServer.h"
#include "LBGameObject.h"

namespace LBNet
{
	/**
		@brief		분산 서버에 사용되는 서버 기본 오브젝트 클래스
		@details	분산 서버의 기본 오브젝트로 샤드와 1:1연결된다.
					분산 서버 로직 구현시 다음 오브젝트를 상속받아
					게임내의 오브젝트 클래스를 구현한다.
		@warning	샤드 오브젝트는 절대 연결 해제하지 않는다.
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