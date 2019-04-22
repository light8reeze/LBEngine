#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <iostream>
#include <Windows.h>
#include "LBBuffer.h"

LBNet::CBuffer<0xFFF, 200> gBuffer;

void Push()
{
	while (1)
	{
		DWORD dwRand = GetTickCount() % 199 + 1;
		char* ptr = new char[dwRand];
		::memset(ptr, 1, dwRand);
		bool aResult = gBuffer.Push(ptr, dwRand);

		delete[] ptr;

		std::this_thread::sleep_for(1ms);
	}
}

void Pop()
{
	while (1)
	{
		char* aData = gBuffer.Pop();

		if (aData != nullptr)
			LB_ASSERT(aData[0] == 1, "Wrong!");
		else
			LB_ASSERT(1 == 1, "Wrong!");

	}
}

int _tmain(int argc, TCHAR argv[])
{
	std::thread t1(Push);
	std::thread t2(Pop);

	t1.join();
	t2.join();

	return 0;
}