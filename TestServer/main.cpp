#include "Main.h"
#include "CTestServer.h"
#include "LBString.h"
#include <iostream>

int main()
{
	CTestServer Server;
	LBNet::CConfig aConfig;

	aConfig.SetSessionCnt(10000);
	aConfig.SetLogBufCnt(30000);
	Server.SetConfig(&aConfig);
	Server.Initialize();
	Server.LazyInitialize();
	Server.Run();
	Server.Close();

	return 0;
}