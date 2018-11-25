#include "ChatServer.h"



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

void CChatServer::AddUser(SOCKET sockCli)
{

}