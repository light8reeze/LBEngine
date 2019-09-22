#include "LBAcceptor.h"
#include "LBIOContext.h"

namespace LBNet
{
	CAcceptor::CAcceptor() : __mAcceptor(CIOContext::Instance().GetIOContext())
	{
	}

	CAcceptor::~CAcceptor()
	{
		Close();
	}

	ErrCode CAcceptor::Bind(const char* pIp, unsigned short pPort)
	{
		LB_ASSERT(pIp != nullptr,			"Ip Error");

		boost::system::error_code aError;
		auto aAddress = asio::ip::make_address(pIp);
		asio::ip::tcp::endpoint aEndPoint(aAddress, pPort);
		__mAcceptor.open(aEndPoint.protocol(), aError);
		__mAcceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
		__mAcceptor.bind(aEndPoint, aError);
		
		return aError.value();
	}

	ErrCode CAcceptor::Bind(unsigned short pPort)
	{
		boost::system::error_code aError;
		asio::ip::tcp::endpoint aEndPoint(boost::asio::ip::tcp::v4(), pPort);
		__mAcceptor.open(aEndPoint.protocol(), aError);
		__mAcceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
		__mAcceptor.bind(aEndPoint, aError);
		return aError.value();
	}

	ErrCode CAcceptor::Listen(int pBackLog)
	{
		LB_ASSERT(__mAcceptor.is_open(), "Acceptor not Open");

		boost::system::error_code aError;
		__mAcceptor.listen(pBackLog, aError);
		return aError.value();
	}

	ErrCode CAcceptor::Accept(CSession& pSession)
	{
		LB_ASSERT(__mAcceptor.is_open(), "Acceptor not Open");

		boost::system::error_code aError;
		__mAcceptor.accept(pSession._mSocket.GetSocket(), aError);
		return aError.value();
	}

	ErrCode CAcceptor::Close()
	{
		boost::system::error_code aError;
		__mAcceptor.close(aError);
		return aError.value();
	}
}