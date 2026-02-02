/**
	@file	LBPacketHeader.h
	@brief	LBServer의 네트워크 패킷 관련 헤더
	@date	2020-04-17
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once

namespace LBNet
{
	using MessageNo = unsigned long;

	/**
		@brief	패킷 헤더 클래스
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