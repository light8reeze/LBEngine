/**
	@file	LBGameObject.h
	@brief	LBServer의 기본 오브젝트 관련 모듈
	@date	2019-09-07
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBSession.h"

namespace LBNet
{
	/**
		@brief		세션과 연결되는 게임 기본 오브젝트 클래스
		@details	게임의 기본 오브젝트로 세션과 1:1연결된다.
					서버 개발 시에는 해당 오브젝트를 상속받아 
					게임내부 오브젝트 클래스를 구현한다.
		@warning	세션과의 연결은 해당 클래스의 함수를 통해서 수행해야 한다.
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
		void SetDisconnect(ErrCode pLastErr = 0);
		ErrCode Send(void* pBuffer, int pSize);
		ErrCode Send(const SharedObject<CSender>& pSender);

		std::string GetIPAddress() const;
		unsigned short GetPort() const;

	protected:
		#pragma warning(disable : 4251)
		WeakObject<CSession> _mSession;
		#pragma warning(default : 4251)
	};
}
