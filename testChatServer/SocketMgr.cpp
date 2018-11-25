#include "SocketMgr.h"
#include "ChatServer.h"
#include "ws2tcpip.h"


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

	this->WaitForUser();
}


CSocketMgr::~CSocketMgr()
{
	closesocket(m_sockListen);
	WSACleanup();
}

void CSocketMgr::WaitForUser()
{
	while (true)
	{
		sockaddr cliAddr;
		int nCliAddrSize = sizeof(cliAddr);
		SOCKET sockCli = accept(m_sockListen, &cliAddr, &nCliAddrSize);
		CChatServer::GetInstance()->AddUser(sockCli);
	}
}