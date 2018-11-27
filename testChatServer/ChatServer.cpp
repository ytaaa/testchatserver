#include "ChatServer.h"

CChatServer* CChatServer::s_pChatServer;
CRITICAL_SECTION CChatServer::m_csCreateIns;

CChatServer::CChatServer()
{
}


CChatServer::~CChatServer()
{
}

CChatServer* CChatServer::GetInstance()
{
	if (s_pChatServer == nullptr)
	{
		EnterCriticalSection(&m_csCreateIns);
		if (s_pChatServer == nullptr)
		{
			s_pChatServer = new CChatServer();
		}
		LeaveCriticalSection(&m_csCreateIns);
	}

	return s_pChatServer;
}

void CChatServer::Init()
{
	InitializeCriticalSection(&m_csCreateIns);
}

void CChatServer::AddUser(SOCKET sockCli)
{
	
}