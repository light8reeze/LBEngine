#include "LBLogger.h"
#include "LBFactory.h"
#include "LBLogProcessor.h"
#include "LBTime.h"
#include <iostream>

namespace LBNet
{
#pragma region CLogBuffer
	CLogBuffer::CLogBuffer() : __mOutput(eOutputNone), __mLogType(ELogType::eLogNone),
							__mBuffer(""), __mUseSize(0)
	{
	}

	void CLogBuffer::Clear()
	{
		__mOutput = eOutputNone;
		__mLogType = ELogType::eLogNone;
		__mUseSize = 0;
		std::fill(__mBuffer, __mBuffer + eSzLogMsg, 0);
	}

	void CLogBuffer::SetLogType(ELogType&& pLogType)
	{
		__mLogType = std::move(pLogType);
	}

	void CLogBuffer::SetLogOutput(LogOutputNo&& pOutput)
	{
		__mOutput = std::move(pOutput);
	}

	char* CLogBuffer::GetBuffer()
	{
		return __mBuffer;
	}

	LogOutputNo CLogBuffer::GetOutput() const
	{
		return __mOutput;
	}

	ELogType CLogBuffer::GetLogType() const
	{
		return __mLogType;
	}

	Size CLogBuffer::GetUseSize() const
	{
		return __mUseSize;
	}

	void CLogBuffer::OnPushed(Size pPushedSize)
	{
		LB_ASSERT(__mUseSize + pPushedSize <= eSzLogMsg, "Over Flow!");

		__mUseSize += pPushedSize;
	}
#pragma endregion CLogBuffer

#pragma region CConsoleLogSystem
	ErrCode CConsoleLogSystem::OnLogging(SharedObject<CLogBuffer>& pBuffer)
	{
		LB_ASSERT(pBuffer != nullptr, "Error!");

		CTime aTime;

		//[yyyy-mm-dd hh:mm:ss] LogType : LogMsg 형식으로 출력한다.
		std::cout << "[" << aTime.GetYear() << "-";
		std::cout.width(2);
		std::cout.fill(0);
		std::cout << aTime.GetMonth() << "-";

		std::cout.width(2);
		std::cout.fill(0);
		std::cout << aTime.GetDay() << " ";

		std::cout.width(2);
		std::cout.fill(0);
		std::cout << aTime.GetHour() << ":";

		std::cout.width(2);
		std::cout.fill(0);
		std::cout << aTime.GetMinute() << ":";

		std::cout.width(2);
		std::cout.fill(0);
		std::cout << aTime.GetSecond() << "]";

		std::cout << " " << CLogger::LogTypeToString(pBuffer->GetLogType()) << ":";
		std::cout << pBuffer->GetBuffer() << std::endl;

		return 0;
	}
#pragma endregion CConsoleLogSystem

#pragma region CLogger
	CLogger::CLogger(ELogType&& pLogType, LogOutputNo&& pOutput) : _mLogBuffer(nullptr)
	{
		_mLogBuffer = CFactory::Instance().New<CLogBuffer>();

		if (_mLogBuffer != nullptr)
		{
			_mLogBuffer->Clear();
			_mLogBuffer->SetLogOutput(std::move(pOutput));
			_mLogBuffer->SetLogType(std::move(pLogType));
		}
	}

	CLogger::~CLogger()
	{
		__SendLog();
	}

	const char* CLogger::LogTypeToString(ELogType&& pLogType)
	{
		switch (pLogType)
		{
		case ELogType::eLogInfo:
			return "Info";
		case ELogType::eLogWarnning:
			return "Warning";
		case ELogType::eLogError:
			return "Error";
		case ELogType::eLogDebug:
			return "Debug";
		case ELogType::eLogCritical:
			return "Critical";
		default:
			LB_ASSERT(0, "Error!");
			return "";
		}
	}

	void CLogger::__SendLog()
	{
		if (_mLogBuffer != nullptr)
		{
			CLogProcessor::Instance().PushLog(std::move(_mLogBuffer));
		}
	}
#pragma endregion CLogger

#pragma region CConsoleLog
	CConsoleLog::CConsoleLog(ELogType&& pLogType) : CLogger(std::move(pLogType), LogOutputNo(eOutputConsole))
	{
		if(_mLogBuffer != nullptr)
			__mLogString.AllocBuffer(_mLogBuffer->GetBuffer(), eSzLogMsg);
	}

	CConsoleLog::~CConsoleLog()
	{
		if (_mLogBuffer != nullptr)
		{
			Size aUseSize = _mLogBuffer->GetUseSize();
			aUseSize = std::min(aUseSize, static_cast<Size>(eSzLogMsg - 1));

			char* aBuffer = _mLogBuffer->GetBuffer();
			aBuffer[aUseSize + 1] = '\0';
		}
	}
#pragma endregion CConsoleLog
}