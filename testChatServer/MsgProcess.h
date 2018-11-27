#pragma once
#include "MsgStruct.h"

void ProcessMsg(MSG_TYPE eType, const char* szBuf, const unsigned int unMsgSize);

void ProcessLogin(const char* szBuf, const unsigned int unMsgSize);