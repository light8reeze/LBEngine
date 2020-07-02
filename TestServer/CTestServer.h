#pragma once
#include "Main.h"
#include "LBGameObject.h"
#include "LBGameServer.h"

class CTestObject : public LBNet::CGameObject
{
public:
	CTestObject() = default;
	~CTestObject() override;

	void OnDisconnect() override;
};

class CTestServer : public LBNet::CGameServer<CTestObject>
{
public:
	CTestServer() = default;
	~CTestServer() override;

	LBNet::ErrCode Initialize() override;
};

