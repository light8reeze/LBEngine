/**
	@file	LBEncyption.h
	@brief	LBUtillity의 암호화 관련 헤더
	@date	2019-04-13
	@auther Light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBUtility.h"

namespace LBNet
{
    /**
        @brief	        암호화 인터페이스
		@details		모든 암호화 관련 클래스는 다음 인터페이스를 상속받아 구현한다.
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