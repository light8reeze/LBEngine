/**
	@file	LBPacketHeader.h
	@brief	LBServer�� ��Ʈ��ũ ��Ŷ ���� ���
	@date	2020-04-17
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once

namespace LBNet
{
	using MessageNo = unsigned long;

	/**
		@brief	��Ŷ ��� Ŭ����
		@date	2019-08-30
		@auther	light8reeze(light8reeze@gmail.com)
	*/
	#pragma pack(push, 1)
	class CPacketHeader
	{
	public:
		MessageNo mMessage;
	};
	#pragma pack(pop)
}