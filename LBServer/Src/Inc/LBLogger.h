/**
	@file	LBLogger.h
	@brief	LBServer�� �α� ��� ���� �������
	@date	2019-12-19
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBServer.h"
#include <type_traits>

namespace LBNet
{
	/**
		@brief		�α� Ÿ�� enum
		@details	�α� ������ Ÿ�Կ� �°� CLogger�� �ִ´�.
	*/
	enum class ELogType : unsigned int
	{
		eLogNone,
		eLogInfo,		// �Ϲ� ���� �α�
		eLogWarnning,	// ��� �α�
		eLogError,		// ���� �α�
		eLogDebug,		// ����׿� �α�
		eLogCritical,	// ġ������ ��Ȳ�� ���� �α�
		eLogTypeCnt,
	};

	/**
		@brief		�α� ��� �ý��� ��ȣ
	*/
	using LogOutputNo = unsigned short;
	constexpr LogOutputNo eOutputNone		= 0;
	constexpr LogOutputNo eOutputConsole	= 1; // �ܼ� �α���� ��ȣ

	/**
		@brief		�α� �޼��� �ִ� ���ڼ�(+ '\0' ���ڼ� 1)
	*/
	constexpr Size eSzLogMsg = 200 + 1;

	/**
		@brief		�α� �޼��� ���� �Ҵ� ����
	*/
	constexpr Size eSzLogBufCnt = 20;

	/**
		@brief		�α� ���� Ŭ����
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
		void	PushLogData(const char*&& pData);

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
		@brief		�α� �ý��� �������̽�
		@details	����� �α� �ý����� ILogSystem�� ��ӹ޾� 
					OnLogging �Լ��� �����Ѵ�.
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
		@brief		�ܼ� �α���� �ý���
		@date	    2019-12-21
		@auther     light8reeze(light8reeze@gmail.com)
	*/
	class CConsoleLogSystem : public ILogSystem
	{
	public:
		CConsoleLogSystem() = default;
		~CConsoleLogSystem() {}

		ErrCode OnLogging(SharedObject<CLogBuffer>& pBuffer) override;
	};

	/**
		@brief		�α� Ŭ����
		@details	1. CLogBuffer�� �޾� ����� �α� �ý��� ���Ŀ� �°� �����Ѵ�.
					2. �α� ����� Timer�� �̿��� �񵿱�� �����Ѵ�.
		
		@warning	1. ���� Ŭ�������� ����� �α׿� �°� CLogBuffer�� ���� ä���.
					2. �����͸� �α� ���ۿ� �����Ҷ� ũ�⿡ �����Ѵ�.
					(eSzLogMsgũ�Ⱑ ��ġ�� ���� �����ʹ� �ڵ����� ��������.)
					3. �α� ������ �ش� ��ü�� �Ҹ�ɶ� �����Ѵ�.
					4. �α� ����Ǯ���� �α� ���۰����� �����ϸ� �αװ� �Ҹ�ȴ�.
					(�α� ���� ������ ó�� ���� �߰� ����
					�α׸� �������̳�? �ƴϸ� �ٷ� ��½�ų���̳�?)
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
		@brief		�ܼ� �α� Ŭ����
		@details	�ܼ� �α���½� ����ϴ� Ŭ�����̴�.
					std::endl�� �ڵ����� ����.
		@date	    2019-12-22
		@auther     light8reeze(light8reeze@gmail.com)
	*/
	class LBS_EXPORT CConsoleLog : public CLogger
	{
	public:
		CConsoleLog(ELogType&& pLogType);
		~CConsoleLog();

		template<typename TArgs, typename TIsScalar = typename std::is_scalar<std::remove_reference_t<TArgs>>::type>
		CConsoleLog& operator<<(TArgs&& pData);

	private:
		// ��Į�� Ÿ���� ��� string���� ��ȯ�� �ִ´�.
		template<typename TArgs>
		CConsoleLog& __PushLogImpl(TArgs&& pData, std::true_type pTrueType);
		template<typename TArgs>
		CConsoleLog& __PushLogImpl(TArgs&& pData, std::false_type pFalseType);
	};
}

#include "LBLogger.Inl"