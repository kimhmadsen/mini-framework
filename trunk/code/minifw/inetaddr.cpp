#include "StdAfx.h"
#include <windows.h>
#include <winsock.h>
#include "inetaddr.h"

INET_Addr::INET_Addr(u_short port, u_long addr)
{
	memset( &addr_ , 0, sizeof( addr_ ) );
	addr_.sin_family = AF_INET;
	addr_.sin_port = htons( port );
	addr_.sin_addr.s_addr = htonl( addr );
}

INET_Addr::INET_Addr(u_short port, char* host)
{
	//int status;

	memset( &addr_ , 0, sizeof( addr_ ) );
	addr_.sin_family = AF_INET;
	addr_.sin_port = htons( port );
	//status = ::inet_aton( host, &addr_ );
	addr_.sin_addr.s_addr =  inet_addr( host );;
}

INET_Addr::INET_Addr(u_short port)
{
	memset( &addr_ , 0, sizeof( addr_ ) );
	addr_.sin_family = AF_INET;
	addr_.sin_port = htons( port );
	addr_.sin_addr.s_addr = htonl( 0 );

}

INET_Addr::~INET_Addr(void)
{

}

void INET_Addr::set_port( u_short port )
{
	addr_.sin_port = htons( port );
}

u_short INET_Addr::get_port()
{
	// convert to host endianess before returning it.
	return ntohs( addr_.sin_port );
}

u_long INET_Addr::get_ip_addr()
{
	// convert to host endianess before returning it.
	return ntohl( addr_.sin_addr.s_addr );
}

sockaddr* INET_Addr::addr(void)
{
	return reinterpret_cast <sockaddr *> (&addr_);
}

size_t INET_Addr::size(void)
{
	return sizeof( addr_ );
}
