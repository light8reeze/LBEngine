#include "CTestServer.h"

int main()
{
	std::cout << "Start!" << std::endl;
	CTestServer Server;
	LBNet::CConfig aConfig;
	LBNet::ErrCode aErrCode;

	aConfig.SetSessionCnt(10000);
	aConfig.AddAddress(54832);
	aConfig.AddAddress(54831);

	Server.SetConfig(&aConfig);
	aErrCode = Server.Initialize();
	if (aErrCode != 0)
	{
		// Error!
		return aErrCode;
	}

	aErrCode = Server.LazyInitialize();
	if (aErrCode != 0)
	{
		// Error!
		return aErrCode;
	}

	aErrCode = Server.Run();
	if (aErrCode != 0)
	{
		// Error!
		return aErrCode;
	}

	aErrCode = Server.Close();
	if (aErrCode != 0)
	{
		// Error!
		return aErrCode;
	}
	
	return 0;
}