#include <vector>
#include "ChatServer.h"
#include "MsgProcess.h"

void ProcessMsg(SOCKET sockUser, MSG_TYPE eType, const char* szBuf, const unsigned int unMsgSize)
{
	switch (eType)
	{
	case MSG_TYPE_LOGIN:
	{
		ProcessLogin(sockUser, szBuf, unMsgSize);
	}
	break;

	case MSG_TYPE_USER_LIST:
	{
		ProcessUserList(sockUser);
	}
	break;

	case MSG_TYPE_CHAT:
	{
		ProcessChat(sockUser, szBuf, unMsgSize);
	}
	break;

	default:
	{
		// error
	}
	break;
	}
}

void ProcessLogin(SOCKET sockUser, const char* szBuf, const unsigned int unMsgSize)
{
	const MSG_LOGIN* pLogin = (const MSG_LOGIN*)szBuf;
	if (pLogin == nullptr)
	{
		return;
	}

	CUser* pUser = CChatServer::GetInstance()->GetUserMgr()->GetUser(sockUser);
	if (pUser)
	{
		pUser->SetName(pLogin->szName);
	}
}

void ProcessUserList(SOCKET sockUser)
{
	char szBuf[MAX_MSG_CONTENT_SIZE] = { 0 };
	MSG_USER_LIST* pUserList = (MSG_USER_LIST*)szBuf;
	std::vector<USER_INFO> vecUserInfo;
	CChatServer::GetInstance()->GetUserMgr()->GetAllUser(vecUserInfo);
	pUserList->unTot = vecUserInfo.size();
	for (size_t i = 0; i < vecUserInfo.size(); ++i)
	{
		pUserList->stInfo[i].id = vecUserInfo[i].id;
		strncpy_s(pUserList->stInfo[i].szName, vecUserInfo[i].szName, MAX_NAME_SIZE);
	}

	CChatServer::GetInstance()->GetSocketMgr()->SendMsgTo(sockUser, szBuf,
		sizeof(MSG_USER_LIST) + vecUserInfo.size() * sizeof(USER_INFO));
}

void ProcessChat(SOCKET sockUser, const char* szBuf, const unsigned int unMsgSize)
{
	MSG_CHAT* pChat = (MSG_CHAT*)szBuf;
	if (!pChat)
	{
		return;
	}

	CUser* pUser = CChatServer::GetInstance()->GetUserMgr()->GetUser(pChat->sockTarget);
	if (!pUser)
	{
		return;
	}

	CChatServer::GetInstance()->GetSocketMgr()->SendMsgTo(pChat->sockTarget, szBuf, unMsgSize);
}