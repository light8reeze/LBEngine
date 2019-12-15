/**
	@file	LBServerConfig.h
	@brief	LBServer�� ���� ���� ���� �������
	@date	2019-12-15
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBServer.h"
#include <thread>

namespace LBNet
{
	/**
		@brief		SAddressInfo ����ü
		@details	Address�������� �����ϴ� ����ü
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
		@brief		CConfig Ŭ����
		@details	���� �������� ������ Ŭ�����̴�.
					������(���Ӽ���App)���� �ʿ�� �� Ŭ������ ��ӹ޾� �����Ѵ�.
		@date		2019-12-15
		@auther		light8reeze(light8reeze@gmail.com)
	*/
	class CConfig
	{
	private:
		using __AddressList = std::vector<SAddressInfo>;

	public:
		CConfig();
		virtual ~CConfig() = default;

		void AddAddress(char* pIP, unsigned int pPort);
		void SetThreadCnt(unsigned pThread);
		void SetSessionCnt(unsigned pSession);
		void SetTimerTaskCnt(unsigned pTimerTask);

		Size GetAddressCnt() const;
		const SAddressInfo& GetAddress(int pIndex) const;
		unsigned GetThreadCnt() const;
		unsigned GetSessionCnt() const;
		unsigned GetTimerTaskCnt() const;

	protected:
		__AddressList	_mAcceptorAddrList;
		unsigned	_mThreadCnt;
		unsigned	_mSessionCnt;
		unsigned	_mTimerTaskCnt;
	};
}

#include "LBConfig.Inl"