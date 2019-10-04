/**
	@file	LBShard.h
	@brief	LBServer의 샤드 관련 헤더
	@date	2019-09-22
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBSession.h"

namespace LBNet
{
	/**
		@brief		TCP 샤드 클래스
		@details	분산서버 연결에 사용된다.
		@warning	1.Connect에 등록되는 핸들러에는 GameObject연결 코드가 반드시 들어가야 한다.
					CSession::SetGameObject를 반드시 호출해야 한다.
					2.Connect에 등록되는 핸들러는 ErrCode(void) 형의 함수이다.
		@date		2019-09-22
		@auther		light8reeze(light8reeze@gmail.com)
	*/
	class CShard : public CSession
	{
	public:
		CShard() = default;
		~CShard() = default;

		template<typename THandler>
		ErrCode Connect(const char* pIp, unsigned short pPort, THandler&& pHandler);

		void	SetServerNo(int pServerNo);
		int		GetServerNo() const;

	private:
		int	__mServerNo;
	};
}

#include "LBShard.Inl"