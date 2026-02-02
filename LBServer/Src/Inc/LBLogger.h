/**
	@file	LBLogger.h
	@brief	LBServer의 로그 모듈 관련 헤더파일
	@date	2019-12-19
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBServer.h"
#include "LBString.h"
#include <type_traits>

namespace LBNet
{
	/**
		@brief		로그 타입 enum
		@details	로그 작성시 타입에 맞게 CLogger에 넣는다.
	*/
	enum class ELogType : unsigned int
	{
		eLogNone,
		eLogInfo,		// 일반 정보 로그
		eLogWarnning,	// 경고 로그
		eLogError,		// 에러 로그
		eLogDebug,		// 디버그용 로그
		eLogCritical,	// 치명적인 상황에 대한 로그
		eLogTypeCnt,
	};

	/**
		@brief		로그 출력 시스템 번호
	*/
	using LogOutputNo = unsigned short;
	constexpr LogOutputNo eOutputNone		= 0;
	constexpr LogOutputNo eOutputConsole	= 1; // 콘솔 로그출력 번호

	/**
		@brief		로그 메세지 최대 문자수(+ '\0' 문자수 1)
	*/
	constexpr Size eSzLogMsg = 200 + 1;

	/**
		@brief		로그 메세지 버퍼 할당 개수
	*/
	constexpr Size eSzLogBufCnt = 20;

	/**
		@brief		로그 버퍼 클래스
        @date	    2019-12-21
        @auther     light8reeze(light8reeze@gmail.com)
	*/
	class LBS_EXPORT CLogBuffer
	{
	public:
		CLogBuffer();
		~CLogBuffer() = default;

		void	Clear();
		void	SetLogType(ELogType&& pLogType);
		void	SetLogOutput(LogOutputNo&& pOutput);

		template<typename TType>
		void	PushLogData(TType& pData);
		template<typename TType>
		void	PushLogData(TType&& pData);
		template<typename TType, Size TSize>
		void	PushLogData(TType (&pData)[TSize]);
		template<typename TType, Size TSize>
		void	PushLogData(TType (&&pData)[TSize]);
		template<>
		void	PushLogData<const char*>(const char*& pData);
		template<>
		void	PushLogData<const char*>(const char*&& pData);
		void	OnPushed(Size pPushedSize);


		char*			GetBuffer();
		LogOutputNo		GetOutput() const;
		ELogType		GetLogType() const;
		Size			GetUseSize() const;

	private:
		LogOutputNo		__mOutput;
		ELogType		__mLogType;
		char			__mBuffer[eSzLogMsg];
		Size			__mUseSize;
	};

	/**
		@brief		로그 시스템 인터페이스
		@details	사용자 로그 시스템은 ILogSystem을 상속받아 
					OnLogging 함수를 구현한다.
        @date	    2019-12-21
        @auther     light8reeze(light8reeze@gmail.com)
	*/
	class ILogSystem
	{
	public:
		ILogSystem() = default;
		virtual ~ILogSystem() {}

		virtual ErrCode OnLogging(SharedObject<CLogBuffer>& pBuffer) = 0;
	};

	/**
		@brief		콘솔 로그출력 시스템
		@date	    2019-12-21
		@auther     light8reeze(light8reeze@gmail.com)
	*/
	class CConsoleLogSystem : public ILogSystem
	{
	public:
		CConsoleLogSystem() = default;
		virtual ~CConsoleLogSystem() {}

		virtual ErrCode OnLogging(SharedObject<CLogBuffer>& pBuffer) override;
	};

	/**
		@brief		로그 클래스
		@details	1. CLogBuffer를 받아 사용자 로그 시스템 방식에 맞게 수행한다.
					2. 로그 수행은 Timer를 이용해 비동기로 수행한다.
		
		@warning	1. 하위 클래스에서는 사용할 로그에 맞게 CLogBuffer에 값을 채운다.
					2. 데이터를 로그 버퍼에 삽입할때 크기에 유의한다.
					(eSzLogMsg크기가 초과할 경우 데이터는 자동으로 제거된다.)
					3. 로그 수행은 해당 객체가 소멸될때 수행한다.
					4. 로그 버퍼풀에서 로그 버퍼가져오기 실패하면 로그가 소멸된다.
					(로그 버퍼 부족시 처리 방식 추가 예정
					로그를 무시하는가? 아니면 바로 출력시키는가?)
		@date	    2019-12-21
		@auther     light8reeze(light8reeze@gmail.com)
	*/
	class LBS_EXPORT CLogger
	{
	public:
		CLogger(ELogType&& pLogType, LogOutputNo&& pOutput);
		virtual ~CLogger();

		template<typename TArgs>
		CLogger& operator<<(TArgs&& pData);

		static const char* LogTypeToString(ELogType&& pLogType);

	private:
		void __SendLog();

	protected:
		#pragma warning(disable : 4251)
		SharedObject<CLogBuffer> _mLogBuffer;
		#pragma warning(default : 4251)
	};

	/**
		@brief		콘솔 로그 클래스
		@details	콘솔 로그출력시 사용하는 클래스이다.
					std::endl은 자동으로 적용.
		@date	    2019-12-22
		@auther     light8reeze(light8reeze@gmail.com)
	*/
	class LBS_EXPORT CConsoleLog : public CLogger
	{
	public:
		CConsoleLog(ELogType&& pLogType = ELogType(ELogType::eLogInfo));
		~CConsoleLog();

		template<typename TArgs, typename TIsScalar = typename std::is_scalar<std::remove_reference_t<TArgs>>::type>
		CConsoleLog& operator<<(TArgs&& pData);

	private:
		// 스칼라 타입인 경우 string으로 변환해 넣는다.
		template<typename TArgs>
		CConsoleLog& __PushLogImpl(TArgs&& pData, std::true_type);
		template<typename TArgs>
		CConsoleLog& __PushLogImpl(TArgs&& pData, std::false_type);

	private:
		#pragma warning(disable : 4251)
		CBufferedString<char> __mLogString;
		#pragma warning(default : 4251)
	};
}

#include "LBLogger.Inl"
