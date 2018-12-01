#include "UserMgr.h"



CUserMgr::CUserMgr():
	m_idAlloc(1)
{
}


CUserMgr::~CUserMgr()
{
}

void CUserMgr::AddUser(SOCKET sockUser)
{
	CUser* pUser = new CUser(m_idAlloc, sockUser);
	if (pUser == nullptr)
	{
		return;
	}

	m_vecUser.push_back(pUser);
	m_mapSock2User[sockUser] = pUser;
}

void CUserMgr::GetAllUser(std::vector<USER_INFO> vecUserInfo)
{
	for (auto iter = m_mapSock2User.begin(); iter != m_mapSock2User.end(); iter++)
	{
		CUser* pUser = (*iter).second;
		if (pUser)
		{
			vecUserInfo.emplace_back((*iter).first, pUser->GetName());
		}
	}
}