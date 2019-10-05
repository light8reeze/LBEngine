/**
	@file	LBSessionManager.h
	@brief	LBServer狼 技记 包府 包访 庆歹(2019-10-05 盒府)
	@date	2019-10-05
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBShardObject.h"
#include "LBShard.h"

namespace LBNet
{
	class LBS_EXPORT CSessionManager
	{
	private:
		using __SessionList = std::vector<SharedObject<CSession>>;
		using __ShardList = std::vector<SharedObject<CSession>>;
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