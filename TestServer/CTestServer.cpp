#include "CTestServer.h"
#include "LBTcpHandler.h"

LBNet::ErrCode Echo(LBNet::CPacketHeader* pHeader, LBNet::Size pSize, LBNet::SharedObject<LBNet::CGameObject>& pObject)
{
	auto aSender = LBNet::CSender::Allocate(pSize);
	auto aHeader = aSender->GetWritePointer<LBNet::CPacketHeader>();
	aHeader->mMessage = 1;

	char* aPtr = aSender->GetWritePointer<char>() + sizeof(LBNet::CPacketHeader);
	return pObject->Send(aSender);
}

CTestObject::~CTestObject()
{
}

CTestServer::~CTestServer()
{
}

void CTestObject::OnDisconnect()
{
	LBNet::CConsoleLog(LBNet::ELogType::eLogInfo) << "On Disconnect";
}

LBNet::ErrCode CTestServer::Initialize()
{
	__super::Initialize();
	LBNet::CSender::Initialize(30000);

	LBNet::CTcpHandler::Instance().Register(1, &Echo);
	
	AddAcceptor(54832);
	AddAcceptor(54831);
	return 0;
}