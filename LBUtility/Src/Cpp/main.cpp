#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <iostream>
#include <Windows.h>
#include "LBBuffer.h"

LBNet::CBuffer<0xFFF, 200> gBuffer;

void Enqueue()
{
	while (1)
	{
		DWORD dwRand = GetTickCount() % 199 + 1;
		char* ptr = new char[dwRand];
		::memset(ptr, 1, dwRand);
		bool aResult = gBuffer.Enqueue(ptr, dwRand);

		delete[] ptr;
	}
}

void Dequeue()
{
	while (1)
	{
		char* aData = gBuffer.Dequeue();

		if(aData != nullptr)
			LB_ASSERT(aData[0] == 1, "Wrong!");
		else
			LB_ASSERT(1 == 1, "Wrong!");

	}
}

int _tmain(int argc, TCHAR argv[])
{
	std::thread t1(Enqueue);
	std::thread t2(Dequeue);

	t1.join();
	t2.join();

	return 0;
}