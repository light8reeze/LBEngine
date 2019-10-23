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
		@details		��� ��ȣȭ ���� Ŭ������ ���� �������̽��� ��ӹ޾� �̱��� ������ �����Ѵ�.
        @date	        2019-10-23
		@warnning		1. �ߺ����� ��ӹ޾� ���� ����.
						2. ������ �������� �������� ���Ѵ�.
						3. �̱��� �ν��Ͻ��� nullptr�� ������ ���� �ִ�.
						(������ Ŭ������ ������ �̱����� nullptr�̴�)
						4. ���� Ŭ���������� ��ȣȭ ����� ũ�⸦ �ݵ�� �����ؾ� �Ѵ�.(_mHeaderSize)
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