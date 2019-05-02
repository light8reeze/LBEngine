/**
	@file	LBIOContext.h
	@brief	LBUtility�� ���� IO���� ���
	@date	2019-05-03
	@auther Light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include <boost/asio/io_context.hpp>

namespace LBNet
{
	/**
		@brief		CIOContext Ŭ����
		@details	boost.asio�� ioservice�� ����ϱ� ���� Ŭ����.
		@date		2019-03-16
		@auther		Light8reeze(light8reeze@gmail.com)
		@todo		Ŭ���� �ϼ�
	*/
	class CIOContext
	{
	public:

	private:
		boost::asio::io_context __mIOContext;
	};
}