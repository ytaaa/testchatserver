#pragma once

extern const int MAX_MSG_SIZE;

enum MSG_TYPE
{
	MSG_TYPE_LOGIN = 1,
};

struct MSG_HEADER
{
	unsigned short usMsgSize;
	MSG_TYPE eMsgType;
};

struct MSG_BASE 
{
	MSG_HEADER stHeader;
	char szBuf[MAX_MSG_SIZE - sizeof(MSG_HEADER)];
};

struct MSG_LOGIN 
{
	char szName[32];
};