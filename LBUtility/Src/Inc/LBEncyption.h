/**
	@file	LBEncyption.h
	@brief	LBUtillity의 암호화 관련 헤더
	@date	2019-04-13
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBUtility.h"

namespace LBNet
{
    /**
        @brief	        암호화 인터페이스
		@details		모든 암호화 관련 클래스는 다음 인터페이스를 상속받아 싱글톤 구조로 구현한다.
        @date	        2019-10-23
		@warnning		1. 중복으로 상속받아 구현 금지.
						2. 스레드 안전성을 보장하지 못한다.
						3. 싱글톤 인스턴스가 nullptr로 설정될 수도 있다.
						(구현된 클래스가 없을시 싱글톤은 nullptr이다)
						4. 하위 클래스에서는 암호화 헤더의 크기를 반드시 설정해야 한다.(_mHeaderSize)
        @auther         light8reeze(light8reeze@gmail.com)
    */
	class LBU_EXPORT CEncryptor
	{
	public:
		CEncryptor();
		virtual ~CEncryptor();

		virtual ErrCode Encypt(char* pData, Size pSize) = 0;
		virtual ErrCode Decypt(char* pData, Size pSize) = 0;
		Size GetHeaderSize();

		static CEncryptor* Instance();

	private:
		static CEncryptor* __mSingleton;

	protected:
		Size _mHeaderSize;
	};
}