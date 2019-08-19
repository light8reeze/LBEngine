#include <stdio.h>
#include "LBAcceptor.h"

using namespace LBNet;

int main()
{
	char test[50];

	CAcceptor aAcceptor;
	aAcceptor.Bind(4832);
	aAcceptor.Listen();

	CTCPSocket aClient;
	aAcceptor.Accept(aClient);

	int aRecv = 0;
	aClient.Receive(test, 13, aRecv);

	printf("Connected!, and Recv : %s\n", test);

	return 0;
}