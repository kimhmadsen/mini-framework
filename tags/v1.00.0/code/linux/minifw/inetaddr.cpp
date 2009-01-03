#include "stdafx.h"
#include "inetaddr.h"
#include <string.h>
#include <arpa/inet.h>

InetAddr::InetAddr(unsigned short port, u_long address)
{
	memset( &addr , 0, sizeof( addr ) );
	addr.sin_family = AF_INET;
	addr.sin_port = htons( port );
	addr.sin_addr.s_addr = htonl( address );
}

InetAddr::InetAddr(unsigned short port, char* host)
{
	//int status;

	memset( &addr , 0, sizeof( addr ) );
	addr.sin_family = AF_INET;
	addr.sin_port = htons( port );
	//status = ::inet_aton( host, &addr );
	addr.sin_addr.s_addr =  inet_addr( host );
}

InetAddr::InetAddr(unsigned short port)
{
	memset( &addr , 0, sizeof( addr ) );
	addr.sin_family = AF_INET;
	addr.sin_port = htons( port );
	addr.sin_addr.s_addr = htonl( 0 );

}

InetAddr::~InetAddr(void)
{

}

void InetAddr::SetPort( u_short port )
{
	addr.sin_port = htons( port );
}

u_short InetAddr::GetPort()
{
	// convert to host endianess before returning it.
	return ntohs( addr.sin_port );
}

u_long InetAddr::GetIpAddr()
{
	// convert to host endianess before returning it.
	return ntohl( addr.sin_addr.s_addr );
}

sockaddr* InetAddr::Addr(void)
{
	return reinterpret_cast <sockaddr *> (&addr);
}

size_t InetAddr::Size(void)
{
	return sizeof( addr );
}
