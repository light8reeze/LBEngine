/**
	@file	LBShard.h
	@brief	LBServer�� ���� ���� ���
	@date	2019-09-22
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBSession.h"

namespace LBNet
{
	/**
		@brief		TCP ���� Ŭ����
		@details	�л꼭�� ���ῡ ���ȴ�.
		@warning	1.Connect�� ��ϵǴ� �ڵ鷯���� GameObject���� �ڵ尡 �ݵ�� ���� �Ѵ�.
					CSession::SetGameObject�� �ݵ�� ȣ���ؾ� �Ѵ�.
					2.Connect�� ��ϵǴ� �ڵ鷯�� ErrCode(void) ���� �Լ��̴�.
		@date		2019-09-22
		@auther		light8reeze(light8reeze@gmail.com)
	*/
	class CShard : public CSession
	{
	public:
		CShard() = default;
		~CShard() = default;

		template<typename THandler>
		ErrCode Connect(const char* pIp, unsigned short pPort, THandler&& pHandler);

		void	SetServerNo(int pServerNo);
		int		GetServerNo() const;

	private:
		int	__mServerNo;
	};
}

#include "LBShard.Inl"