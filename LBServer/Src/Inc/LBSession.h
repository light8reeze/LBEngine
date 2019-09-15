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
#include "LBManagedObject.h"
#include "LBFactory.h"

namespace LBNet
{
	/**
		@brief		오브젝트 키 클래스
		@details	한 서버 내에서 관리되는 세션, 게임 오브젝트의 키 값이다.
					이 키를 이용해서 세션, 게임 오브젝트를 찾을 수 있다.
		@warning	1. CObjectKey값은 세션끼리 겹치게 하면 안된다.(한 서버 내에 유일해야 한다)
					2. 연결된 세션, 게임 오브젝트 간에는 반드시 오브젝트 키가 같아야 한다.
		@date		2019-09-12
		@auther		light8reeze(light8reeze@gmail.com)
	*/
	class CObjectKey
	{
	public:
		CObjectKey() = default;
		CObjectKey(const CObjectKey& pRValue) : mKey(pRValue.mKey) {}
		CObjectKey(const CObjectKey&& pRValue) : mKey(std::move(pRValue.mKey)) {}
		~CObjectKey() = default;

		CObjectKey& operator=(const CObjectKey& pRValue)
		{
			mKey = pRValue.mKey;
		}
		bool operator==(const CObjectKey& pRValue)
		{
			return mKey == pRValue.mKey;
		}
		bool operator!=(const CObjectKey& pRValue)
		{
			return !(this->operator==(pRValue));
		}
		bool operator>(const CObjectKey& pRValue)
		{
			return mKey > pRValue.mKey;
		}

	public:
		union
		{
			unsigned int mKey;
			struct
			{
				unsigned mIndex : 27;
				unsigned mIsSet : 1;
				unsigned mReuse : 4;
			};
		};
	};

	class CGameObject;

	/**
		@brief	TCP 세션 클래스
		@date	2019-08-19
		@auther	light8reeze(light8reeze@gmail.com)
	*/
	class LBS_EXPORT CSession : public CManagedObject
	{
		friend class CAcceptor; // Acceptor에서 소켓 접근이 필요하다.

	public:
		enum class EState
		{
			eStable,
			eDisconnect,
		};

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
		void SetObject(SharedObject<TObject>& pObject);
		void RemoveObject();

		template<typename TObject>
		SharedObject<TObject> GetGameObject();

	protected:
		ErrCode _OnDelete() override;

	private:
		CTCPSocket					__mSocket;
		__BufferType				__mBuffer;
		CLocker						__mLocker;
		EState						__mState;
		SharedObject<CGameObject>	__mGameObject;
		CObjectKey					__mObjectKey;
	};
}

#include "LBSession.Inl"