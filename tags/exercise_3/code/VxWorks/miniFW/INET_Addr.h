#pragma once

#include <sockLib.h>
#include <stdlib.h>
#include <inetLib.h> 
#include <string.h>

class INET_Addr
{
public:
	INET_Addr(u_short port, u_long addr);
	INET_Addr(u_short port, char* host);
	INET_Addr(u_short port);
	~INET_Addr(void);
	void set_port( u_short port );
	u_short get_port(void);
	u_long get_ip_addr(void);
	sockaddr* addr(void);
	size_t size(void);
private:
	sockaddr_in addr_;
};
