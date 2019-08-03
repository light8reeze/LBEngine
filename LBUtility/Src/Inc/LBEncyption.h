/**
	@file	LBEncyption.h
	@brief	LBUtillity�� ��ȣȭ ���� ���
	@date	2019-04-13
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBUtility.h"

namespace LBNet
{
    /**
        @brief	        ��ȣȭ �������̽�
		@details		��� ��ȣȭ ���� Ŭ������ ���� �������̽��� ��ӹ޾� �����Ѵ�.
        @date	        2019-04-13
		@todo			��ȣȭ ��� ���� ����
        @auther         light8reeze(light8reeze@gmail.com)
    */
	class IEncyption
	{
	public:
		IEncyption() = default;
		virtual ~IEncyption() = 0;
	};

	class CCrc16 : public IEncyption
	{
	public:
		CCrc16() = default;
		virtual ~CCrc16() = default;
	};
}