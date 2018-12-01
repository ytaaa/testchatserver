#pragma once
#include <vector>
#include <map>
#include "User.h"

class CUserMgr
{
public:
	CUserMgr();
	~CUserMgr();

public:
	void AddUser(SOCKET sockUser);
	void GetAllUser(std::vector<USER_INFO> vecUserInfo);

public:
	CUser* GetUser(SOCKET sock) { return m_mapSock2User.find(sock) != m_mapSock2User.end() ? m_mapSock2User[sock] : nullptr; }

private:
	std::vector<CUser*> m_vecUser;
	std::map<SOCKET, CUser*> m_mapSock2User;
	unsigned int m_idAlloc;
};

