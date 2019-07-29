/**
	@file	LBBoostConfig.h
	@brief	LBUtility�� boost ���̺귯���� ����ϱ� ���� �ʿ��� ���� ������� 
			���� boost���� ���� LBUtility.h�� �����ϱ� ���� LB_USE_CUSTOM_BOOST_CONFIG��ũ�θ� �����Ѵ�.
	@date	2019-05-04
	@auther Light8reeze(light8reeze@gmail.com)
*/
#pragma once

/**
	@brief	boost c++17 allocator ���� ��� ����<L6>
*/
#define _SILENCE_CXX17_ALLOCATOR_VOID_DEPRECATION_WARNING

/**
	@brief	boost lib �̻�� ����
*/
#define BOOST_DATE_TIME_NO_LIB
#define BOOST_REGEX_NO_LIB