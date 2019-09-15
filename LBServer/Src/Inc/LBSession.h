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
	/**
		@brief		������Ʈ Ű Ŭ����
		@details	�� ���� ������ �����Ǵ� ����, ���� ������Ʈ�� Ű ���̴�.
					�� Ű�� �̿��ؼ� ����, ���� ������Ʈ�� ã�� �� �ִ�.
		@warning	1. CObjectKey���� ���ǳ��� ��ġ�� �ϸ� �ȵȴ�.(�� ���� ���� �����ؾ� �Ѵ�)
					2. ����� ����, ���� ������Ʈ ������ �ݵ�� ������Ʈ Ű�� ���ƾ� �Ѵ�.
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