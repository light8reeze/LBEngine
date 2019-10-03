/**
	@file	LBGameObject.h
	@brief	LBServer�� �⺻ ������Ʈ ���� ���
	@date	2019-09-07
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBServer.h"
#include "LBSession.h"
#include "LBLocker.h"
#include <queue>

namespace LBNet
{
	/**
		@brief		���ǰ� ����Ǵ� ���� �⺻ ������Ʈ Ŭ����
		@details	������ �⺻ ������Ʈ�� ���ǰ� 1:1����ȴ�.
					���� ���� ������ ���� ������Ʈ�� ��ӹ޾� 
					���ӳ��� ������Ʈ Ŭ������ �����Ѵ�.
		@warning	���ǰ��� ������ ���� Ŭ������ �Լ��� ���ؼ� �������Ѿ� �Ѵ�.
		@date		2019-09-07
		@auther		light8reeze(light8reeze@gmail.com)
	*/
	class LBS_EXPORT CGameObject
	{
	public:
		CGameObject();
		virtual ~CGameObject() {};

	public:
		void LinkSession(SharedObject<CSession>& pSession);
		void Unlink();
		virtual void OnAccept() = 0;
		ErrCode Send(void* pBuffer, int pSize);

		const CSessionKey GetSessionKey() const;

	protected:
		WeakObject<CSession> _mSession;
	};

	class LBS_EXPORT CSessionManager
	{
	private:
		using __SessionList		= std::vector<SharedObject<CSession>>;
		using __SessionKeyQueue = std::queue<CSessionKey>;

	public:
		CSessionManager() = default;
		void Initialize(int pMaxSession);
		template<typename TObject>
		SharedObject<TObject> GetGameObject(CSessionKey& pKey);
		SharedObject<CSession> GetSession(CSessionKey& pKey);
		void Close();

		CSessionKey GetKey();
		void ReturnKey(CSessionKey& aKey);

		static CSessionManager& Instance();
	private:
		static CSessionManager	__mSingleton;
		__SessionList			__mSessionList;
		__SessionKeyQueue		__mWaitQueue;
		CSharedMutex			__mMutex;
	};
}

#include "LBGameObject.Inl"