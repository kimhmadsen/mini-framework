#pragma once

#include <windows.h>
#include <winsock.h>
#include <stdlib.h>
//
//typedef WORD u_short;
//typedef DWORD u_long;

class INET_Addr
{
public:
	INET_Addr(u_short port, u_long addr);
	~INET_Addr(void);
	u_short get_port(void);
	u_long get_ip_addr(void);
	sockaddr* addr(void);
	size_t size(void);
private:
	sockaddr_in addr_;
};
