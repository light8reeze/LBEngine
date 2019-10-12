/**
	@file	LBShard.h
	@brief	LBServer의 샤드 관련 헤더
	@date	2019-09-22
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBShardObject.h"

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
	template<typename TShardObject>
	class CShard : public CSession
	{
	public:
		CShard();
		~CShard() = default;

		virtual ErrCode Initialize() override;
		ErrCode			Connect();
		virtual ErrCode SetDisconnect() override;

		void				SetAddress(const char* pIp, unsigned short pPort);
		void				SetServerNo(unsigned short pServerNo);
		unsigned short		GetServerNo() const;
		virtual void		OnDelete() override;

	private:
		void __OnConnectFail(ErrCode pErr);

	private:
		unsigned short	__mServerNo;
		std::string		__mIp;
		unsigned short	__mPort;
		bool			__mNextConnect;
	};
}

#include "LBShard.Inl"