#pragma once
#include "LBServer.h"

/**
	@brief		LBServer 라이브러리 사용 설정
*/
#ifdef _DEBUG
	#ifdef X64
		#pragma comment (lib, "LBServerD_x64.lib")
	#elif WIN32
		#pragma comment (lib, "LBServerD_x86.lib")
	#endif
#else
	#ifdef X64
		#pragma comment (lib, "LBServer_x64.lib")
	#elif WIN32
		#pragma comment (lib, "LBServer_x86.lib")
	#endif
#endif //_DEBUG