/**
	@file	LBLogProcessor.h
	@brief	LBServer의 로그 처리 관련 헤더파일
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
		@brief		로그 처리기
		@details	전송받은 로그 메세지를 출력하는 역할을 한다.
		@warning	로그는 직렬화 하여 한 쓰레드에서 처리하도록 한다.
					(ProcessLog가 여러 쓰레드에서 호출되면 안된다.)
		@date	    2019-12-22
		@auther     light8reeze(light8reeze@gmail.com)
	*/
	class LBS_EXPORT CLogProcessor
	{
	private:
		using __LogSysList	= std::unordered_map<LogOutputNo, UniqueObject<ILogSystem>>;
		using __LogQueue	= std::deque<SharedObject<CLogBuffer>>;
		using __Flag		= std::atomic<bool>;

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
		CSharedMutex		__mMutex;
		#ifdef _DEBUG
		std::thread::id		__mProcessID {};
		#endif //_DEBUG
		#pragma warning(default : 4251)
	};
}

#include "LBLogProcessor.Inl"