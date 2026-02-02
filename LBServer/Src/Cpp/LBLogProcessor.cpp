#include "LBLogProcessor.h"
#include "LBTimer.h"

namespace LBNet
{
	CLogProcessor CLogProcessor::__mSingleton;

	CLogProcessor::CLogProcessor() : __mLogSystemList(), __mLogQueue(),
									__mIsProcess(false)
	{
		AddLogSystem<CConsoleLogSystem>(LogOutputNo(eOutputConsole));
	}

	CLogProcessor& CLogProcessor::Instance()
	{
		return __mSingleton;
	}

	bool CLogProcessor::PushLog(SharedObject<CLogBuffer>&& pLogBuf)
	{
		LB_ASSERT(pLogBuf != nullptr, "Error!");

		{
			WriteLock aWriteLock(*this);
			__mLogQueue.emplace_back(std::move(pLogBuf));
		}

		bool aFalseValue = false;
		if (__mIsProcess.compare_exchange_strong(aFalseValue, true))
		{
			CTimer::Start(1ms, [this](ErrCode pErr)
			{
				LB_ASSERT(__mIsProcess == true,					"Error");
				LB_ASSERT(__mProcessID == std::thread::id(),	"Error");

				DEBUG_CODE(__mProcessID = std::this_thread::get_id());

				if(pErr == 0)
					ProcessLog();

				DEBUG_CODE(__mProcessID = std::thread::id());
				__mIsProcess.store(false);
			});
		}

		return true;
	}

	ErrCode CLogProcessor::ProcessLog()
	{
		LB_ASSERT(__mIsProcess == true,							"Error");
		LB_ASSERT(__mProcessID == std::this_thread::get_id(),	"Error");

		SharedObject<CLogBuffer> aBuffer = nullptr;
		bool					aIsEmpty = true;

		{
			WriteLock aWriteLock(*this);

			aIsEmpty = __mLogQueue.empty();
			if (aIsEmpty)
			{
				return 0;
			}

			aBuffer = __mLogQueue.front();
			__mLogQueue.pop_front();
		}

		while (!aIsEmpty)
		{
			LB_ASSERT(aBuffer != nullptr,	"Error");

			const auto& aLogOutIter = __mLogSystemList.find(aBuffer->GetOutput());
			if (aLogOutIter != __mLogSystemList.end())
				aLogOutIter->second->OnLogging(aBuffer);

			{
				WriteLock aWriteLock(*this);

				aIsEmpty = __mLogQueue.empty();
				if (!aIsEmpty)
				{
					aBuffer = __mLogQueue.front();
					__mLogQueue.pop_front();
				}
			}
		}

		return 0;
	}
}