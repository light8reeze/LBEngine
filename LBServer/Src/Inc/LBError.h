/**
	@file	LBError.h
	@brief	LBServer의 에러코드 관련 헤더파일
	@date	2019-10-22
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once

LB_ERRCODE(eErrCodeSesDisconnected);
LB_ERRCODE(eErrCodeSesBufferFull);
LB_ERRCODE(eErrCodeInvalidSize);
LB_ERRCODE(eErrCodeNullSender);
LB_ERRCODE(eErrCodeNotEnoughRsc);
LB_ERRCODE(eErrCodeAlreadyRegistered);
LB_ERRCODE(eErrCodeInvalidMessage);
LB_ERRCODE(eErrCodeBadAlloc);
LB_ERRCODE(eErrCodeNullPtr);
LB_ERRCODE(eErrCodeInvalidThreadCnt);
LB_ERRCODE(eErrCodeInvalidConfig);