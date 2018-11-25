#pragma once
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
	void AddUser(SOCKET sockCli);

private:
	static CChatServer* s_pChatServer;
	static CRITICAL_SECTION m_csCreateIns;
	CSocketMgr *m_pSockMgr;
};

