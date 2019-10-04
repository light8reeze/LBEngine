/**
	@file	LBGameServer.h
	@brief	LBServer�� ���Ӽ��� ���� ���
	@date	2019-09-22
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBServer.h"
#include "LBAcceptor.h"
#include "LBGameObject.h"
#include "LBFactory.h"
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
		using __TAcceptorList	= std::vector<CAcceptor>;

	public:
		using GameObject = TGameObject;

	public:
		CGameServer();
		virtual ~CGameServer();

		void AddAcceptor(const char* pIp, unsigned short pPort);
		void AddAcceptor(unsigned short pPort);
		void SetThreadCount(unsigned int pThread = 0);
		void SetSessionMax(unsigned int pSession);

		unsigned int GetThreadCount();
		unsigned int GetAcceptorCount();
		unsigned int GetSessionMax();

		virtual ErrCode SetParameter() = 0;
		virtual ErrCode Initialize();
		virtual ErrCode LazyInitialize();
		virtual ErrCode Close();
		ErrCode Run();

	private:
		void		__Main();
		ErrCode		__SetAccept(CAcceptor& pAcceptor);

	private:
		__TThreadList	__mThreadList;
		__TAcceptorList	__mAcceptorList;

		unsigned int	__mThreadCnt;
		unsigned int	__mMaxSession;

	protected:
		CSharedMutex	_mMutex;
	};
}

#include "LBGameServer.Inl"