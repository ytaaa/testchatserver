#include "User.h"


CUser::CUser(const unsigned int id, SOCKET sock):
	m_id(id),
	m_sock(sock)
{
}


CUser::~CUser()
{
}
