/**
	@file	LBIOContext.h
	@brief	LBUtility의 소켓 IO관련 헤더
	@date	2019-05-03
	@auther Light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include <boost/asio/io_context.hpp>

namespace LBNet
{
	/**
		@brief		CIOContext 클래스
		@details	boost.asio의 ioservice를 사용하기 위한 클래스.
		@date		2019-03-16
		@auther		Light8reeze(light8reeze@gmail.com)
		@todo		클래스 완성
	*/
	class CIOContext
	{
	public:

	private:
		boost::asio::io_context __mIOContext;
	};
}