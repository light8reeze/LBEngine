#include "CTestServer.h"
#include <iostream>

CTestObject::~CTestObject()
{
}

void CTestObject::OnAccept()
{
}

CTestServer::CTestServer()
{
	__mShard = new LBNet::CShard();
}

CTestServer::~CTestServer()
{
	delete __mShard;
}

LBNet::ErrCode CTestServer::SetParameter()
{
	SetThreadCount();
	AddAcceptor(4833);

	LBNet::CMessageHandler::Register(1, &(CTestServer::Echo));

	return 0;
}

LBNet::ErrCode CTestServer::LazyInitialize()
{
	__super::LazyInitialize();

	LBNet::CShard*& aShard = __mShard;
	CTestPacket& aPacket = __mPacket;

	__mShard->Connect("127.0.0.1", 4832, 
		[Shard = __mShard, &Packet = __mPacket]()
	{
		auto aObject = LBNet::SharedObject<CTestObject>(new CTestObject);

		Shard->SetObject(aObject);
		Packet.mCommand = 1;
		Packet.mDataSize = sizeof(CTestPacket);
		Packet.mNum = 1;

		return Shard->Send((void*)&Packet, Packet.mDataSize);
	});

	return 0;
}

LBNet::ErrCode CTestServer::Echo(LBNet::CPacketHeader* pData, LBNet::Size pDataSize, LBNet::SharedObject<LBNet::CGameObject>& pObject)
{
	int* aData = (int*)(pData + 1);
	std::cout << (*aData) << std::endl;
	return 0;
}