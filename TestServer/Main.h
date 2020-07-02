#pragma once
#define LOAD_LBCLIENT
#include "LBClient.h"

/**
	@brief		LBClient ���̺귯�� ��� ����
*/
#ifdef _DEBUG
	#ifdef X64
		#pragma comment (lib, "LBClientD_x64.lib")
	#elif WIN32
		#pragma comment (lib, "LBClientD_x86.lib")
	#endif
#else
	#ifdef X64
		#pragma comment (lib, "LBClient_x64.lib")
	#elif WIN32
		#pragma comment (lib, "LBClient_x86.lib")
	#endif
#endif //_DEBUG