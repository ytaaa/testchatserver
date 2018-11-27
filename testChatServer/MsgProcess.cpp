#include "MsgProcess.h"

void ProcessMsg(MSG_TYPE eType, const char* szBuf, const unsigned int unMsgSize)
{
	switch (eType)
	{
	case MSG_TYPE_LOGIN:
	{
		ProcessLogin(szBuf, unMsgSize);
	}
	break;

	default:
	{
		// error
	}
	break;
	}
}