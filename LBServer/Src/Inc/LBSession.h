/**
	@file	LBSession.h
	@brief	LBServer�� ��Ʈ��ũ ���� ���� ���
	@date	2019-08-19
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBServer.h"
#include "LBSocket.h"
#include "LBBuffer.h"
#include "LBLocker.h"
#include "LBSender.h"
#include "LBTcpHandler.h"

namespace LBNet
{
	class CGameObject;

	/**
		@brief		TCP ���� Ŭ����
		@warning	1. ����� ����, ���� ������Ʈ�� �ݵ�� 1:1������ �ؾ��Ѵ�.
		@date		2019-08-19
		@auther		light8reeze(light8reeze@gmail.com)
	*/
	class LBS_EXPORT CSession
	{
		friend class CAcceptor; // Acceptor���� ���� ������ �ʿ��ϴ�.

	public:
		enum class EState
		{
			eStable,
			eDisconnect,
			eClosed,
		};

	public:
		CSession();
		virtual ~CSession();

		virtual ErrCode Initialize();
		ErrCode OnAccept();
		ErrCode Receive();
		ErrCode OnReceive(Size pSize);
		ErrCode Send(void* pBuffer, int pSize);
		ErrCode Send(SharedObject<CSender> pSender);
		virtual ErrCode Close();
		virtual ErrCode SetDisconnect(ErrCode pError = 0);

		const CTcpSocket::EndPointType& GetEndPoint() const;

		template<typename TObject>
		void SetGameObject(SharedObject<TObject>& pObject);
		void SetShared(SharedObject<CSession> pShared);
		void RemoveObject();

		template<typename TObject = CGameObject>
		SharedObject<TObject>	GetGameObject();
		SharedObject<CSession>	GetShared();

		static bool Delete(CSession* pObject);

	private:
		template<typename TObject>
		SharedObject<TObject> __GetGameObjectImpl(std::true_type);
		template<typename TObject>
		SharedObject<TObject> __GetGameObjectImpl(std::false_type);

	protected:
		CTcpSocket					_mSocket;
		CSharedMutex				_mMutex;
		EState						_mState;
		ErrCode						_mLastError;

	private:
		CBuffer						__mBuffer;
		#pragma warning(disable : 4251)
		SharedObject<CSession>		__mInstance;
		SharedObject<CGameObject>	__mGameObject;
		#pragma warning(default : 4251)
	};
}

#include "LBSession.Inl"