/**
	@file	LBConfig.h
	@brief	LBServer의 서버 설정 관련 헤더파일
	@date	2019-12-15
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBServer.h"
#include <thread>

namespace LBNet
{
	/**
		@brief		SAddressInfo 구조체
		@details	Address설정값을 보관하는 구조체
		@date		2019-12-15
		@auther		light8reeze(light8reeze@gmail.com)
	*/
	struct SAddressInfo
	{
		SAddressInfo(char* pIp, unsigned int pPort);
		SAddressInfo(std::string pIp, unsigned int pPort);

		std::string		mIp = "";
		unsigned short	mPort = 0;
	};

	/**
		@brief		CConfig 클래스
		@details	서버 설정값을 저장한 클래스이다.
					하위단(게임서버App)에서 필요시 이 클래스를 상속받아 구현한다.
		@date		2019-12-15
		@auther		light8reeze(light8reeze@gmail.com)
	*/
	class CConfig
	{
	protected:
		using _AddressList = std::vector<SAddressInfo>;

	public:
		CConfig();
		virtual ~CConfig() = default;

		void AddAddress(char* pIP, unsigned int pPort);
		void AddAddress(unsigned int pPort);
		void SetThreadCnt(unsigned pThread);
		void SetSessionCnt(unsigned pSession);
		void SetTimerTaskCnt(unsigned pTimerTask);
		void SetLogBufCnt(unsigned pTimerTask);

		Size GetAddressCnt() const;
		const SAddressInfo& GetAddress(int pIndex) const;
		unsigned GetThreadCnt() const;
		unsigned GetSessionCnt() const;
		unsigned GetTimerTaskCnt() const;
		unsigned GetLogBufCnt() const;

	protected:
		_AddressList	_mAcceptorAddrList;		// Acceptor 개수
		unsigned	_mThreadCnt;				// 사용 쓰레드 개수
		unsigned	_mSessionCnt;				// 최대 세션 수
		unsigned	_mTimerTaskCnt;				// 타이머 자원 최대 개수
		unsigned	_mLogBufCnt;				// 로그용 버퍼 최대 개수
	};
}

#include "LBConfig.Inl"