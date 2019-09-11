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
#include "LBManagedObject.h"
#include "LBFactory.h"

namespace LBNet
{
	class CGameObject;

	/**
		@brief	TCP ���� Ŭ����
		@date	2019-08-19
		@auther	light8reeze(light8reeze@gmail.com)
	*/
	class LBS_EXPORT CSession : public CManagedObject
	{
		friend class CAcceptor; // Acceptor���� ���� ������ �ʿ��ϴ�.

	public:
		enum class EState
		{
			eStable,
			eDisconnect,
		};

	public:
		using ObjectPtr = CFactory::ObjectPtr<CGameObject>;

	private:
		using __BufferType	= CAsyncBuffer<eSzPacketBuffer, eSzPacketMax>;

	public:
		CSession();
		~CSession();

		ErrCode Initialize();
		ErrCode OnAccept();
		ErrCode Receive();
		ErrCode OnReceive(int pSize);
		ErrCode Send(void* pBuffer, int pSize);
		ErrCode Close();
		ErrCode SetDisconnect();

		template<typename TObject>
		void SetObject(CFactory::ObjectPtr<TObject>& pObject);
		void RemoveObject();
		ObjectPtr GetGameObject();

	protected:
		ErrCode _OnDelete() override;

	private:
		CTCPSocket		__mSocket;
		__BufferType	__mBuffer;
		CLocker			__mLocker;
		EState			__mState;
		ObjectPtr		__mGameObject;
	};
}

#include "LBSession.Inl"