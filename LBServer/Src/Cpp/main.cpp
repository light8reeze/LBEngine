#include "CTestServer.h"

int main()
{
	auto aTest(std::make_shared<CTestServer>());
	aTest->SetParameter();
	aTest->Initialize();
	aTest->LazyInitialize();
	aTest->Run();
	aTest->Close();
	return 0;
}