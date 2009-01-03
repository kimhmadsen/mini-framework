#pragma once

#include <windows.h>
#include <winsock.h>
#include <stdlib.h>

/**
Implement a Wrapper Facade for sockaddr_in data structure.

Responsibility:
- Emcapsulates non-object-oriented functions and data-structures with a cohesive object-oriented abstraction.

Collaborator:
- sockaddr_in
*/
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
