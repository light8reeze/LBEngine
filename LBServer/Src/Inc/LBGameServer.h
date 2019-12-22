/**
	@file	LBGameServer.h
	@brief	LBServer�� ���Ӽ��� ���� ���
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
		@brief				���Ӽ��� Ŭ����
		@details			���� ���� ���η��� Ŭ�����̴�. 
							1. Game Application������ ���� Ŭ������ ��ӹ޾� �����Ѵ�.
							2. ���� ������ ���� ������� �����Ѵ�.
							(SetParameter -> Initialize -> LazyInitialize -> Run -> Close)
							3. AddAcceptor�� �ݵ�� SetParameter���� �����Ѵ�.
		@param TGameObject	���� �������� ���ǿ� ����� ���� ������Ʈ Ÿ��.
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