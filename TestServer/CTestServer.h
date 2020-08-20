#pragma once
#include "AppDefines.h"
#include "LBGameObject.h"
#include "LBGameServer.h"

class CPacketEcho : public LBNet::CPacketHeader
{
public:
	CPacketEcho() = default;
	~CPacketEcho() = default;

	int mData;
};

class CTestObject : public LBNet::CGameObject
{
public:
	CTestObject() = default;
	~CTestObject() = default;

	void OnAccept() override;
	void OnDisconnect() override;
};

class CTestServer : public LBNet::CGameServer<CTestObject>
{
public:
	CTestServer() = default;
	~CTestServer() override;

	LBNet::ErrCode Initialize() override;
	LBNet::ErrCode LazyInitialize() override;
	LBNet::ErrCode Close() override;
};

