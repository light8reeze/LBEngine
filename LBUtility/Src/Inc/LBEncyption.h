/**
	@file	LBEncyption.h
	@brief	LBUtillity�� ��ȣȭ ���� ���
	@date	2019-04-13
	@auther Light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBUtility.h"

namespace LBNet
{
    /**
        @brief	        ��ȣȭ �������̽�
		@details		��� ��ȣȭ ���� Ŭ������ ���� �������̽��� ��ӹ޾� �����Ѵ�.
        @date	        2019-04-13
        @auther         Light8reeze(light8reeze@gmail.com)
    */
	class IEncyption
	{
	public:
		IEncyption() = default;
		virtual ~IEncyption() = 0;
	};
}