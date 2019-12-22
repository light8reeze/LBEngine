/**
	@file	LBGameServer.h
	@brief	LBServer의 게임서버 관련 헤더
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
		@details			게임 서버 메인로직 클래스이다. 
							1. Game Application구현시 다음 클래스를 상속받아 구현한다.
							2. 실행 순서는 다음 순서대로 실행한다.
							(SetParameter -> Initialize -> LazyInitialize -> Run -> Close)
							3. AddAcceptor은 반드시 SetParameter에서 실행한다.
		@param TGameObject	게임 서버에서 세션에 사용할 게임 오브젝트 타입.
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

		void AddAcceptor(const char* pIp, unsigned short pPort);
		void AddAcceptor(unsigned short pPort);

		void SetConfig(CConfig* pConfig);
		virtual ErrCode Initialize();
		virtual ErrCode LazyInitialize();
		virtual ErrCode Close();
		ErrCode Run();

		unsigned int GetAcceptorCount();

	private:
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