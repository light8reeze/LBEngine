#include <tchar.h>
#include <iostream>
#include "LBProbability.h"

int _tmain(int argc, TCHAR argv[])
{
	int aArr[5] = {0, 20, 20, 30, 30};
	int aCnt[5] = {0, };

	for (int i = 0; i < 1000000; ++i)
	{
		int aResult = LBNet::CProbability::GetChoice(aArr);
		LB_ASSERT(aResult != 5, "a");

		aCnt[aResult]++;
	}

	for (int& a : aCnt)
	{
		std::cout << a << std::endl;
	}
	return 0;
}