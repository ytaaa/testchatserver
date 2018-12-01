#pragma once
#include "MsgStruct.h"

void ProcessMsg(SOCKET sockUser, MSG_TYPE eType, const char* szBuf, const unsigned int unMsgSize);

void ProcessLogin(SOCKET sockUser, const char* szBuf, const unsigned int unMsgSize);
void ProcessUserList(SOCKET sockUser);
void ProcessChat(SOCKET sockUser, const char* szBuf, const unsigned int unMsgSize);