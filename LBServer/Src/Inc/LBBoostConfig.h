/**
	@file	LBBoostConfig.h
	@brief	LBUtility의 boost 라이브러리를 사용하기 위해 필요한 설정 헤더파일 
			직접 boost설정 사용시 LBUtility.h를 포함하기 전에 LB_USE_CUSTOM_BOOST_CONFIG매크로를 정의한다.
	@date	2019-05-04
	@auther Light8reeze(light8reeze@gmail.com)
*/
#pragma once

/**
	@brief	boost c++17 allocator 관련 경고 삭제<L6>
*/
#define _SILENCE_CXX17_ALLOCATOR_VOID_DEPRECATION_WARNING

/**
	@brief	boost lib 미사용 설정
*/
#define BOOST_DATE_TIME_NO_LIB
#define BOOST_REGEX_NO_LIB