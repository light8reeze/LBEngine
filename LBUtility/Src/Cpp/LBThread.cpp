#include "LBThread.h"

namespace LBNet
{
	/**
		@brief CThread�� ������
	*/
	CThread::CThread() : __mThread(), __mResult(-1), __mSwitchingTime(0), __mLastSwitchingTime()
	{
		__mLastSwitchingTime = std::chrono::system_clock::now();
	}

	/**
		@brief CThread�� �Ҹ���
	*/
	CThread::~CThread()
	{
	}

	/**
		@brief	������ Ŭ������ �����ϴ� �Լ�.
		@return	������ ���� �����
	*/
	int CThread::Initialize()
	{
		return 0;
	}

	/**
		@brief	������ �����ϴ� �Լ�.
		@return	������ ���� �����
	*/
	int CThread::StartThread()
	{
		auto alpfnThread = std::bind(&CThread::ThreadRoutine, this);
		__mThread			= std::thread(alpfnThread);

		return 0;
	}

	/**
		@brief		������ ������� ����ϴ� �Լ�
		@warning	�� �Լ��� �����ϸ� �����尡 ����ɶ����� block���°� �˴ϴ�.
		@return		������ ���� ���
	*/
	int CThread::JoinThread()
	{
		if(__mThread.joinable() == true)
			__mThread.join();

		return __mResult;
	}

	/**
		@brief		�������� ID���� �޴� �Լ�
		@return		�������� ID��
	*/
	CThread::id CThread::GetThreadId() const
	{
		return __mThread.get_id();
	}

	/**
		@brief		�����尡 ����ɶ� �����ϴ� ��ƾ�Լ�
	*/
	void CThread::ThreadRoutine()
	{
		__mResult = Main();
	}
}