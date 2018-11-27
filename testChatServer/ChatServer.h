#pragma once
#undef _WINSOCKAPI_
#define _WINSOCKAPI_
#include <windows.h>
#include "SocketMgr.h"

class CChatServer
{
private:
	CChatServer();
public:
	~CChatServer();

public:
	static CChatServer* GetInstance();

	CSocketMgr* GetSocketMgr() { return m_pSockMgr; }
	void AddUser(SOCKET sockCli);

private:
	static void Init();
	static CChatServer* s_pChatServer;
	static CRITICAL_SECTION m_csCreateIns;
	CSocketMgr *m_pSockMgr;
};

