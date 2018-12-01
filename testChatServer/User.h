#pragma once
#include "define.h"

class CUser
{
public:
	CUser(const unsigned int id, SOCKET sock);
	~CUser();

public:
	void SetName(const char* szName) { strncpy_s(m_szName, szName, MAX_NAME_SIZE); }
	const char* GetName() { return m_szName; }

private:
	SOCKET m_sock;
	const unsigned int m_id;
	char m_szName[MAX_NAME_SIZE];
};

