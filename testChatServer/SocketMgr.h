#include <winsock2.h>
#pragma once

const char* IP = "127.0.0.1";
const unsigned int PORT = 12345;
const int BACKLOG = 20;

class CSocketMgr
{
public:
	CSocketMgr();
	~CSocketMgr();

public:
	void WaitForUser();

private:
	SOCKET m_sockListen;
};

