#pragma once
#include "LBServer.h"
#include "LBGameServer.h"
#include "LBHandler.h"
#include "LBShard.h"

#pragma pack(push, 1)
class CTestPacket : public LBNet::CBufferHeader, public LBNet::CPacketHeader
{
public:
	int mNum;
};
#pragma pack(pop)

class CTestObject : public LBNet::CGameObject
{
public:
	CTestObject() = default;
	~CTestObject();

	void OnAccept();

private:
};

class CTestServer : public LBNet::CGameServer<CTestObject>
{
public:
	CTestServer();
	~CTestServer();

	LBNet::ErrCode SetParameter() override;
	LBNet::ErrCode LazyInitialize() override;

	static LBNet::ErrCode Echo(LBNet::CPacketHeader* pData, LBNet::Size pDataSize, LBNet::SharedObject<LBNet::CGameObject>& pObject);

private:
	LBNet::CShard*	__mShard;
	CTestPacket		__mPacket;
};