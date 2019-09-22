/**
	@file	LBGameServer.h
	@brief	LBServer의 게임서버 관련 헤더
	@date	2019-09-22
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBServer.h"
#include <thread>

namespace LBNet
{
	/**
		@brief				게임서버 클래스
		@details			게임 서버 메인로직 클래스이다. 
							Game Application구현시 다음 클래스를 상속받아 구현한다.
		@param TGameObject	게임 서버에서 세션에 사용할 게임 오브젝트 타입.
		@date				2019-09-22
		@auther				light8reeze(light8reeze@gmail.com)
	*/
	template<typename TGameObject>
	class CGameServer
	{
	public:
		using GameObject = TGameObject;

	public:
		CGameServer();
		virtual ~CGameServer();

		ErrCode Initialize(int pWorkThread = 1);
		ErrCode Run();
		ErrCode Close();

	private:
		std::vector<std::thread> __mThreadList;
	};
}