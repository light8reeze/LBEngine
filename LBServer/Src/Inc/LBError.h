/**
	@file	LBError.h
	@brief	LBServer�� �����ڵ� ���� �������
	@date	2019-10-22
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once

namespace LBNet
{
	LB_ERRCODE(eErrCodeSesDisconnected);
	LB_ERRCODE(eErrCodeSesBufferFull);
	LB_ERRCODE(eErrCodeInvalidSize);
	LB_ERRCODE(eErrCodeNullSender);
	LB_ERRCODE(eErrCodeNotEnoughRsc);
	LB_ERRCODE(eErrCodeAlreadyRegistered);
	LB_ERRCODE(eErrCodeInvalidMessage);
	LB_ERRCODE(eErrCodeBadAlloc);
}