/**
	@file	LBPool.h
	@brief	LBUtillity의 오브젝트 풀관련 헤더
	@date	2019-04-10
	@auther Light8reeze(light8reeze@gmail.com)
*/
#pragma once

namespace LBNet
{

    /**
        @brief	        오브젝트 풀 클래스
        @details        원형버퍼 구조로 데이터를 보관한다. 스레드에 안전하다.(추후 테스트)
        @param TObject	사용할 객체의 타입
        @param TCount	생성할 오브젝트 개수
        @date	        2019-04-10
        @todo           오브젝트 풀 완성
        @auther         Light8reeze(light8reeze@gmail.com)
    */
	template<class TObject, Size TCount>
	class CObjectPool
	{
	};
}