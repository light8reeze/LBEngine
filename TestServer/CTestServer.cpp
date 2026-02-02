#include "CTestServer.h"
#include "LBTcpHandler.h"

LBNet::ErrCode Echo(LBNet::CPacketHeader* pHeader, LBNet::Size pSize, LBNet::SharedObject<LBNet::CGameObject>& pObject)
{
	auto aEchoPacket = reinterpret_cast<CPacketEcho*>(pHeader);
	LBNet::CConsoleLog(LBNet::ELogType::eLogInfo) << "Echo Data : " << aEchoPacket->mData;

	// 패킷 Send를 위해 Send에서 메모리 버퍼를 받아 사용한다.
	auto aSender = LBNet::CSender::Allocate<CPacketEcho>();
	auto aPacket = aSender->GetWritePointer<CPacketEcho>();
	aPacket->mMessage	= 1;
	aPacket->mData		= aEchoPacket->mData;

	return pObject->Send(aSender);
}

void CTestObject::OnAccept()
{
	LBNet::CConsoleLog(LBNet::ELogType::eLogInfo) << "On Accept";
}

void CTestObject::OnDisconnect()
{
	LBNet::CConsoleLog(LBNet::ELogType::eLogInfo) << "On Disconnect";
}

CTestServer::~CTestServer()
{
}

LBNet::ErrCode CTestServer::Initialize()
{
	LBNet::ErrCode aErrCode = __super::Initialize();
	if (aErrCode != 0)
		return aErrCode;

	LBNet::CSender::Initialize(30000);

	// 패킷 이벤트 추가
	aErrCode = LBNet::CTcpHandler::Instance().Register(1, &Echo);
	if (aErrCode != 0)
		return aErrCode;

	return 0;
}

LBNet::ErrCode CTestServer::LazyInitialize()
{
	LBNet::ErrCode aErrCode = __super::LazyInitialize();
	if (aErrCode != 0)
		return aErrCode;

	return 0;
}

LBNet::ErrCode CTestServer::Close()
{
	return __super::Close();
}