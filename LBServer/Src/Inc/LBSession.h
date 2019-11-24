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
#include "LBManagedObject.h"
#include "LBSender.h"
#include "LBHandler.h"

namespace LBNet
{
	class CGameObject;

	/**
		@brief		TCP ��Ŷ �̺�Ʈ Ÿ�� ����
	*/
	using TCPHandleType = std::function<ErrCode(CPacketHeader*, Size, SharedObject<CGameObject>&)>;
	using TCPHandler	= CMessageHandler<TCPHandleType>;

	/**
		@brief		���� Ű�� null�� ����
	*/
	constexpr unsigned int eKeyNull = std::numeric_limits<unsigned int>::max();

	/**
		@brief		���� Ű Ŭ����
		@details	�� ���� ������ �����Ǵ� ����, ���� ������Ʈ�� Ű ���̴�.
					�� Ű�� �̿��ؼ� ����, ���� ������Ʈ�� ã�� �� �ִ�.
		@warning	1. CSessionKey���� ���ǳ��� ��ġ�� �ϸ� �ȵȴ�.(�� ���� ���� �����ؾ� �Ѵ�)
		@date		2019-09-12
		@auther		light8reeze(light8reeze@gmail.com)
	*/
	class CSessionKey
	{
	public:
		CSessionKey() : mKey(eKeyNull) {}
		CSessionKey(unsigned int pKey) : mKey(pKey) {}
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
				unsigned mIndex : eSzSessionIndexMax;	// ���� ���� �ε���
				unsigned mType	: 2;	// ���� Ÿ��(0: �Ϲ� ����, 1: ����)
				unsigned mIsSet : 1;	// ���� �Ǿ��ִ� ����
				unsigned mReuse : 4;	// ���� Ƚ��(0 ~ 2^4)
				unsigned mEtc	: 8;	// ��Ÿ ���п� ��ȣ
			}mField;
		};
	};

	/**
		@brief		TCP ���� Ŭ����
		@warning	1. ����� ����, ���� ������Ʈ�� �ݵ�� 1:1������ �ؾ��Ѵ�.
		@date		2019-08-19
		@auther		light8reeze(light8reeze@gmail.com)
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
		CSession();
		virtual ~CSession() override;

		virtual ErrCode Initialize();
		ErrCode OnAccept();
		ErrCode Receive();
		ErrCode OnReceive(Size pSize);
		ErrCode Send(void* pBuffer, int pSize);
		ErrCode Send(SharedObject<CSender> pSender);
		virtual ErrCode Close();
		virtual ErrCode SetDisconnect();

		void SetSessionKey(CSessionKey& pObjKey);
		const CSessionKey& GetSessionKey() const;
		CSessionKey GetSessionKey();
		const CTcpSocket::EndPointType& GetEndPoint() const;

		template<typename TObject>
		void SetGameObject(SharedObject<TObject>& pObject);
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

	protected:
		CTcpSocket					_mSocket;
		CSharedMutex				_mMutex;
		CSessionKey					_mSessionKey;
		EState						_mState;

	private:
		CBuffer						__mBuffer;
		SharedObject<CGameObject>	__mGameObject;
	};
}

#include "LBSession.Inl"