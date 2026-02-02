/**
	@file	LBLogProcessor.h
	@brief	LBServer�� �α� ó�� ���� �������
	@date	2019-12-22
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBServer.h"
#include "LBLogger.h"
#include "LBLocker.h"
#include <deque>

namespace LBNet
{
	/**
		@brief		�α� ó����
		@details	���۹��� �α� �޼����� ����ϴ� ������ �Ѵ�.
		@warning	�α״� ����ȭ �Ͽ� �� �����忡�� ó���ϵ��� �Ѵ�.
					(ProcessLog�� ���� �����忡�� ȣ��Ǹ� �ȵȴ�.)
		@date	    2019-12-22
		@auther     light8reeze(light8reeze@gmail.com)
	*/
	class LBS_EXPORT CLogProcessor
	{
	private:
		using __LogSysList	= std::unordered_map<LogOutputNo, UniqueObject<ILogSystem>>;
		using __LogQueue	= std::deque<SharedObject<CLogBuffer>>;
		using __Flag		= std::atomic<bool>;

		LB_LOCKOBJECT(CLogProcessor, CSharedMutex);

	private:
		CLogProcessor();

	public:
		~CLogProcessor() = default;
		static CLogProcessor& Instance();

		template<typename TLogSystem>
		void AddLogSystem(LogOutputNo&& pOutput);

		bool	PushLog(SharedObject<CLogBuffer>&& pLogBuf);
		ErrCode ProcessLog();

	private:
		static CLogProcessor __mSingleton;

		#pragma warning(disable : 4251)
		__LogSysList		__mLogSystemList;
		__LogQueue			__mLogQueue;
		__Flag				__mIsProcess;
		#ifdef _DEBUG
		std::thread::id		__mProcessID {};
		#endif //_DEBUG
		#pragma warning(default : 4251)
	};
}

#include "LBLogProcessor.Inl"