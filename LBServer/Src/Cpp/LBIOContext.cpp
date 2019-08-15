#include "LBIOContext.h"

namespace LBNet
{
	CIOContext::~CIOContext()
	{
		__mIOContext.stop();
	}

	ErrCode CIOContext::Run()
	{
		__mIOContext.run();
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