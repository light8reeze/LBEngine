#include <stdio.h>
#include "LBAcceptor.h"
#include "LBIOContext.h"

using namespace LBNet;

int main()
{
	char test[50];

	CAcceptor aAcceptor;
	aAcceptor.Bind(4832);
	aAcceptor.Listen();

	CTCPSocket aClient;
	aAcceptor.AcceptAsync(aClient, 
		[&aClient](boost::system::error_code error)
	{
		printf("Accepted!\n");
	});

	CIOContext::Instance().Run();

	int aRecv = 0;
	aClient.Receive(test, 13, aRecv);

	printf("Connected!, and Recv : %s\n", test);

	return 0;
}