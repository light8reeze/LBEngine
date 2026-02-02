#include "LBIOContext.h"

namespace LBNet
{
	CIOContext CIOContext::__mSingleton;

	CIOContext::CIOContext() : __mIOContext(), __mStrand(__mIOContext), __mWork(__mIOContext)
	{
	}

	CIOContext::~CIOContext()
	{
	}

	ErrCode CIOContext::Run()
	{
		return __mIOContext.run();
	}

	void CIOContext::Stop()
	{
		__mIOContext.stop();
	}

	void CIOContext::Restart()
	{
		__mIOContext.restart();
	}

	asio::io_context& CIOContext::GetIOContext()
	{
		return __mIOContext;
	}

	CIOContext& CIOContext::Instance()
	{
		return __mSingleton;
	}
}