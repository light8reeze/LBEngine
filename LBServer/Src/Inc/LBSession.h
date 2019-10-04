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

namespace LBNet
{
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
				unsigned mIndex : eSzSessionIndexMax;	// ���� ���� �ε���
				unsigned mType	: 2;	// ���� Ÿ��(0: �Ϲ� ����, 1: ����)
				unsigned mIsSet : 1;	// ���� �Ǿ��ִ� ����
				unsigned mReuse : 4;	// ���� Ƚ��(0 ~ 2^4)
				unsigned mEtc	: 8;	// ��Ÿ ���п� ��ȣ
			}mField;
		};
	};

	class CGameObject;

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