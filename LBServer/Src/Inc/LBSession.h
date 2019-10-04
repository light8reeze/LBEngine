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

namespace LBNet
{
	/**
		@brief		세션 키 클래스
		@details	한 서버 내에서 관리되는 세션, 게임 오브젝트의 키 값이다.
					이 키를 이용해서 세션, 게임 오브젝트를 찾을 수 있다.
		@warning	1. CSessionKey값은 세션끼리 겹치게 하면 안된다.(한 서버 내에 유일해야 한다)
		@date		2019-09-12
		@auther		light8reeze(light8reeze@gmail.com)
	*/
	class CSessionKey
	{
	public:
		CSessionKey() : mKey(0) {}
		CSessionKey(const CSessionKey& pRValue) : mKey(pRValue.mKey) {}
		CSessionKey(const CSessionKey&& pRValue) : mKey(std::move(pRValue.mKey)) {}
		~CSessionKey() = default;

		CSessionKey& operator=(const CSessionKey& pRValue)
		{
			mKey = pRValue.mKey;
			return (*this);
		}
		bool operator==(const CSessionKey& pRValue)
		{
			return mKey == pRValue.mKey;
		}
		bool operator!=(const CSessionKey& pRValue)
		{
			return !(this->operator==(pRValue));
		}
		bool operator>(const CSessionKey& pRValue)
		{
			return mKey > pRValue.mKey;
		}

	public:
		union
		{
			unsigned int mKey;
			struct CKeyBit
			{
				unsigned mIndex : eSzSessionIndexMax;	// 세션 종류 인덱스
				unsigned mType	: 2;	// 세션 타입(0: 일반 세션, 1: 샤드)
				unsigned mIsSet : 1;	// 설정 되어있는 여부
				unsigned mReuse : 4;	// 재사용 횟수(0 ~ 2^4)
				unsigned mEtc	: 8;	// 기타 구분용 번호
			}mField;
		};
	};

	class CGameObject;

	/**
		@brief		TCP 세션 클래스
		@warning	1. 연결된 세션, 게임 오브젝트는 반드시 1:1연결을 해야한다.
		@date		2019-08-19
		@auther		light8reeze(light8reeze@gmail.com)
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
		using __BufferType	= CBuffer<eSzPacketMax>;

	public:
		CSession();
		virtual ~CSession() override;

		ErrCode Initialize();
		ErrCode OnAccept();
		ErrCode Receive();
		ErrCode OnReceive(Size pSize);
		ErrCode Send(void* pBuffer, int pSize);
		ErrCode Close();
		ErrCode SetDisconnect();

		void SetSessionKey(CSessionKey& pObjKey);
		const CSessionKey& GetSessionKey() const;
		CSessionKey GetSessionKey();

		template<typename TObject>
		void SetObject(SharedObject<TObject>& pObject);
		void RemoveObject();

		template<typename TObject = CGameObject>
		SharedObject<TObject> GetGameObject();

	private:
		template<typename TObject>
		SharedObject<TObject> __GetGameObjectImpl(std::true_type);
		template<typename TObject>
		SharedObject<TObject> __GetGameObjectImpl(std::false_type);

	public:
		virtual void OnDelete() override;

	private:
		__BufferType				__mBuffer;
		CLocker						__mLocker;
		EState						__mState;
		SharedObject<CGameObject>	__mGameObject;
		CSessionKey					__mSessionKey;

	protected:
		CTCPSocket					_mSocket;
	};
}

#include "LBSession.Inl"