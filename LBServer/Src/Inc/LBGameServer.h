/**
	@file	LBGameServer.h
	@brief	LBServer의 게임서버 관련 모듈
	@date	2019-09-22
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBServer.h"
#include "LBAcceptor.h"
#include "LBFactory.h"
#include "LBTimer.h"
#include "LBUdpObject.h"
#include "LBConfig.h"
#include "LBLogger.h"
#include <thread>

namespace LBNet
{
	/**
		@brief				게임서버 클래스
		@details			서버 관련 메인로직 클래스이다. 
							1. Game Application에서는 해당 클래스를 상속받아 구현한다.
							2. 서버 실행은 아래 순서대로 수행한다.
							(SetConfig -> Initialize -> LazyInitialize -> Run -> Close)
		@param TGameObject	서버 내부에서 세션에 연결된 게임 오브젝트 타입.
		@date				2019-09-22
		@auther				light8reeze(light8reeze@gmail.com)
	*/
	template<typename TGameObject>
	class CGameServer
	{
	private:
		using __TThreadList		= std::vector<std::thread>;
		using __TAcceptorList	= std::vector<UniqueObject<CAcceptor>>;

	public:
		using GameObject = TGameObject;

	public:
		CGameServer();
		virtual ~CGameServer();

		void SetConfig(CConfig* pConfig);
		virtual ErrCode Initialize();
		virtual ErrCode LazyInitialize();
		virtual ErrCode Close();
		ErrCode Run();

		unsigned int GetAcceptorCount();

	private:
		void		__AddAcceptor(const char* pIp, unsigned short pPort);
		void		__AddAcceptor(unsigned short pPort);

		void		__Main();
		ErrCode		__SetAccept(CAcceptor* pAcceptor);

	private:
		__TThreadList	__mThreadList;
		__TAcceptorList	__mAcceptorList;

	protected:
		CConfig* _mConfig;
	};
}

#include "LBGameServer.Inl"
