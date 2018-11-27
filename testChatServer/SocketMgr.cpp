#include "SocketMgr.h"
#include "ChatServer.h"
#include "ws2tcpip.h"
#include "MsgStruct.h"
#include "MsgProcess.h"

const char* IP = "127.0.0.1";
const unsigned int PORT = 12345;
const int BACKLOG = 20;
const int MAX_MSG_SIZE = 1024;

DWORD WINAPI ListenThread(LPVOID lpParameter)
{
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

DWORD WINAPI UserMsgThread(LPVOID lpParameter)
{
	const SOCKET sockCli = *(SOCKET*)lpParameter;
	char szRecvBuf[MAX_MSG_SIZE - sizeof(MSG_HEADER)] = { 0 };
	MSG_HEADER stHeader;
	while (true)
	{
		recv(sockCli, (char*)&stHeader, sizeof(MSG_HEADER), 0);
		recv(sockCli, szRecvBuf, stHeader.usMsgSize, 0);
		ProcessMsg(stHeader.eMsgType, szRecvBuf, stHeader.usMsgSize);
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
	inet_pton(AF_INET, IP, &svrAddr.sin_addr);
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
