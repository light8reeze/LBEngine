/**
	@file	LBSessionManager.h
	@brief	LBServer�� ���� ���� ���� ���
	@date	2019-10-05
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBShard.h"
#include "LBLocker.h"
#include <queue>

namespace LBNet
{
	/**
		@brief	        ���� �Ŵ��� Ŭ����
		@details		����, �л꼭���� ����, �����Ѵ�.
		@date	        2019-09-29
		@auther         light8reeze(light8reeze@gmail.com)
	*/
	class LBS_EXPORT CSessionManager
	{
	private:
		using __SessionList		= std::vector<SharedObject<CSession>>;
		using __ShardList		= std::vector<SharedObject<CSession>>;
		using __SessionKeyQueue = std::queue<CSessionKey>;

	public:
		CSessionManager() = default;
		void Initialize(int pMaxSession);
		template<typename TObject>
		SharedObject<TObject> GetGameObject(CSessionKey& pKey);
		SharedObject<CSession> GetSession(CSessionKey& pKey);
		void Close();

		template<typename TShardObject>
		void AddShard(unsigned short pSvrNo, const char* pIp, unsigned short pPort);
		SharedObject<CSession> GetShard(CSessionKey& pKey);
		void InitShard();

		CSessionKey GetKey();
		void ReturnKey(CSessionKey& aKey);

		static CSessionManager& Instance();
	private:
		static CSessionManager	__mSingleton;
		__SessionList			__mSessionList;
		__ShardList				__mShardList;
		__SessionKeyQueue		__mWaitQueue;
		CSharedMutex			__mMutex;
	};
}

#include "LBSessionManager.Inl"