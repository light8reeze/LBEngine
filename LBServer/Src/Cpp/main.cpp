#include "CTestServer.h"

int main()
{
	CTestServer aTest;
	aTest.SetParameter();
	aTest.Initialize();
	aTest.LazyInitialize();
	aTest.Run();
	aTest.Close();
	return 0;
}