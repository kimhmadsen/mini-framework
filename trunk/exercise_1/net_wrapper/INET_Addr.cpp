#include "StdAfx.h"
#include "INET_Addr.h"

INET_Addr::INET_Addr(u_short port, u_long addr)
{
	memset( &addr_ , 0, sizeof( addr_ ) );
	addr_.sin_family = AF_INET;
	addr_.sin_port = htons( port );
	addr_.sin_addr.s_addr = htonl( addr );
}

INET_Addr::~INET_Addr(void)
{

}

u_short INET_Addr::get_port()
{
	return addr_.sin_port;
}

u_long INET_Addr::get_ip_addr()
{
	return addr_.sin_addr.s_addr;
}

sockaddr* INET_Addr::addr(void)
{
	return reinterpret_cast <sockaddr *> (&addr_);
}

size_t INET_Addr::size(void)
{
	return sizeof( addr_ );
}
