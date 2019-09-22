/**
	@file	LBGameServer.h
	@brief	LBServer�� ���Ӽ��� ���� ���
	@date	2019-09-22
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBServer.h"
#include <thread>

namespace LBNet
{
	/**
		@brief				���Ӽ��� Ŭ����
		@details			���� ���� ���η��� Ŭ�����̴�. 
							Game Application������ ���� Ŭ������ ��ӹ޾� �����Ѵ�.
		@param TGameObject	���� �������� ���ǿ� ����� ���� ������Ʈ Ÿ��.
		@date				2019-09-22
		@auther				light8reeze(light8reeze@gmail.com)
	*/
	template<typename TGameObject>
	class CGameServer
	{
	public:
		using GameObject = TGameObject;

	public:
		CGameServer();
		virtual ~CGameServer();

		ErrCode Initialize(int pWorkThread = 1);
		ErrCode Run();
		ErrCode Close();

	private:
		std::vector<std::thread> __mThreadList;
	};
}