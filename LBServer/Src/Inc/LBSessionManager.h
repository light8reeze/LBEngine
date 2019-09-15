/**
	@file	LBSessionManager.h
	@brief	LBServer狼 技记包府磊 包访 庆歹
	@date	2019-09-12
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBServer.h"
#include "LBGameObject.h"

namespace LBNet
{
	/**
		@brief		技记 包府磊 努贰胶
		@date		2019-09-12
		@auther		light8reeze(light8reeze@gmail.com)
	*/
	class LBS_EXPORT CSessionManager
	{
	private:
		using __SessionList		= std::vector<CSession>;
		using __SessionQueue	= std::queue<CSession>;

	public:
		CSessionManager();
		~CSessionManager();

		template<typename TObject>
		CFactory::ObjectPtr<TObject> GetGameObject();

		CSessionManager& Instance();

	private:
		static CSessionManager __mSingleton;

	private:
		__SessionList	__mList;
		__SessionQueue	__mQueue;
	};
}