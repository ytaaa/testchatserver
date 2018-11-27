#pragma once
#include <winsock2.h>
#include <vector>

class CSocketMgr
{
public:
	CSocketMgr();
	~CSocketMgr();

public:
	void AddUserSocket(SOCKET sockCli) { m_vecUserSocket.push_back(sockCli); }
	void AddUserMsgThread(HANDLE hUserMsgThread) { m_vecUserMsgThread.push_back(hUserMsgThread); }

private:
	SOCKET m_sockListen;
	HANDLE m_hProc;
	std::vector<SOCKET> m_vecUserSocket;
	std::vector<HANDLE> m_vecUserMsgThread;
};

