#pragma once

#include <windows.h>
#include <winsock.h>
#include <stdlib.h>

class InetAddr
{
public:
	InetAddr(u_short port, u_long addr);
	InetAddr(u_short port, char* host);
	InetAddr(u_short port);
	~InetAddr(void);
	void SetPort( u_short port );
	u_short GetPort(void);
	u_long GetIpAddr(void);
	sockaddr* Addr(void);
	size_t Size(void);
private:
	sockaddr_in addr;
};
