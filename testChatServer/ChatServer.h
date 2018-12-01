#pragma once
#undef _WINSOCKAPI_
#define _WINSOCKAPI_
#include <windows.h>
#include "SocketMgr.h"
#include "UserMgr.h"

class CChatServer
{
private:
	CChatServer();
public:
	~CChatServer();

public:
	static void Init();
	static CChatServer* GetInstance();

	CSocketMgr* GetSocketMgr() { return m_pSockMgr; }
	CUserMgr* GetUserMgr() { return m_pUserMgr; }

private:
	static CChatServer* s_pChatServer;
	static CRITICAL_SECTION m_csCreateIns;
	CSocketMgr* m_pSockMgr;
	CUserMgr* m_pUserMgr;
};

