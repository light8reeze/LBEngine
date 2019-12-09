/**
	@file	LBSession.h
	@brief	LBServer의 네트워크 세션 관련 헤더
	@date	2019-08-19
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBServer.h"
#include "LBSocket.h"
#include "LBBuffer.h"
#include "LBLocker.h"
#include "LBSender.h"
#include "LBHandler.h"

namespace LBNet
{
	class CGameObject;

	/**
		@brief		TCP 패킷 이벤트 타입 정의
	*/
	using TCPHandleType = std::function<ErrCode(CPacketHeader*, Size, SharedObject<CGameObject>&)>;
	
	#pragma warning(disable : 4251)
	class LBS_EXPORT CTcpHandler : public CMessageHandler<TCPHandleType>
	{
	private:
		CTcpHandler() = default;

		static CTcpHandler __mSingleton;

	public:
		static CTcpHandler& Instance();
	};
	#pragma warning(default : 4251)

	/**
		@brief		TCP 세션 클래스
		@warning	1. 연결된 세션, 게임 오브젝트는 반드시 1:1연결을 해야한다.
		@date		2019-08-19
		@auther		light8reeze(light8reeze@gmail.com)
	*/
	class LBS_EXPORT CSession
	{
		friend class CAcceptor; // Acceptor에서 소켓 접근이 필요하다.

	public:
		enum class EState
		{
			eStable,
			eDisconnect,
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
		virtual ErrCode SetDisconnect();

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

	private:
		CBuffer						__mBuffer;
		#pragma warning(disable : 4251)
		SharedObject<CSession>		__mInstance;
		SharedObject<CGameObject>	__mGameObject;
		#pragma warning(default : 4251)
	};
}

#include "LBSession.Inl"