#include "LBTime.h"
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <iostream>
#include "LBLocker.h"
#include <mutex>
#include <Windows.h>

#define THREAD 8
#define LOOP 100000

std::mutex gMutex;
LBNet::CLocker gLocker;
CRITICAL_SECTION gCS;

long long gSum = 0;

void TestCustomSpinLock()
{
	gSum = 0;
	std::thread aThread[THREAD];
	DWORD aStart = GetTickCount();
	//54456
	for (std::thread& t : aThread)
	{
		t = std::thread([]
		{
			for (int i = 0; i < LOOP; ++i)
			{
				gLocker.lock();
				gSum += i;
				gLocker.unlock();
			}
		});
	}

	for (std::thread& t : aThread)
	{
		t.join();
	}

	DWORD aEndTime = GetTickCount();

	std::cout << "SpinTime : " << (aEndTime - aStart) << std::endl;
	std::cout << "Spin : " << gSum << std::endl;
}

void TestMutex()
{
	gSum = 0;
	std::thread aThread[THREAD];
	DWORD aStart = GetTickCount();
	//54456
	for (std::thread& t : aThread)
	{
		t = std::thread([]
		{
			for (int i = 0; i < LOOP; ++i)
			{
				gMutex.lock();
				gSum += i;
				gMutex.unlock();
			}
		});
	}

	for (std::thread& t : aThread)
	{
		t.join();
	}

	DWORD aEndTime = GetTickCount();

	std::cout << "MutexTime : " << (aEndTime - aStart) << std::endl;
	std::cout << "Mutex : " << gSum << std::endl;
}

void TestCS()
{
	gSum = 0;
	std::thread aThread[THREAD];
	InitializeCriticalSection(&gCS);
	DWORD aStart = GetTickCount();
	//54456
	for (std::thread& t : aThread)
	{
		t = std::thread([]
		{
			for (int i = 0; i < LOOP; ++i)
			{
				EnterCriticalSection(&gCS);
				gSum += i;
				LeaveCriticalSection(&gCS);
			}
		});
	}

	for (std::thread& t : aThread)
	{
		t.join();
	}

	DWORD aEndTime = GetTickCount();

	std::cout << "CS Time : " << (aEndTime - aStart) << std::endl;
	std::cout << "CS : " << gSum << std::endl;
}

int _tmain(int argc, TCHAR argv[])
{
	TestCustomSpinLock();
	TestCS();
	TestMutex();
	return 0;
}