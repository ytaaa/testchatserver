#include "ChatServer.h"
#include "ws2tcpip.h"
#include "MsgProcess.h"

DWORD WINAPI UserMsgThread(LPVOID lpParameter)
{
	if (lpParameter == NULL)
	{
		return 0;
	}

	const SOCKET sockCli = *(SOCKET*)lpParameter;
	CChatServer::GetInstance()->GetUserMgr()->AddUser(sockCli);
	char szRecvBuf[MAX_MSG_SIZE] = { 0 };
	MSG_HEADER stHeader;
	while (true)
	{
		recv(sockCli, (char*)&stHeader, sizeof(MSG_HEADER), 0);
		recv(sockCli, szRecvBuf, stHeader.usMsgSize, 0);
		ProcessMsg(sockCli, stHeader.eMsgType, szRecvBuf, stHeader.usMsgSize);
	}

	return 0;
}

DWORD WINAPI ListenThread(LPVOID lpParameter)
{
	if (lpParameter == NULL)
	{
		return 0;
	}

	const SOCKET sockListen = *(SOCKET*)lpParameter;
	while (true)
	{
		sockaddr cliAddr;
		int nCliAddrSize = sizeof(cliAddr);
		SOCKET sockCli = accept(sockListen, &cliAddr, &nCliAddrSize);
		CChatServer::GetInstance()->GetSocketMgr()->AddUserSocket(sockCli);
		HANDLE hProc = CreateThread(NULL, 0, UserMsgThread, (LPVOID)&sockCli, 0, 0);
		CChatServer::GetInstance()->GetSocketMgr()->AddUserMsgThread(hProc);
	}

	return 0;
}

CSocketMgr::CSocketMgr()
{
	WSADATA data;
	WSAStartup(MAKEWORD(2, 2), &data);

	m_sockListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in svrAddr;
	memset(&svrAddr, 0, sizeof(svrAddr));
	svrAddr.sin_family = AF_INET;
	inet_pton(AF_INET, SVRIP, &svrAddr.sin_addr);
	svrAddr.sin_port = htons(PORT);
	bind(m_sockListen, (sockaddr*)& svrAddr, sizeof(sockaddr));

	listen(m_sockListen, BACKLOG);

	m_hProc = CreateThread(NULL, 0, ListenThread, (LPVOID)(&m_sockListen), 0, NULL);
}


CSocketMgr::~CSocketMgr()
{
	closesocket(m_sockListen);
	WSACleanup();
}

void CSocketMgr::SendMsgTo(SOCKET sockTarget, const char* szBuf, unsigned int unMsgSize)
{
	send(sockTarget, szBuf, unMsgSize, 0);
}