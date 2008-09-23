#include "StdAfx.h"
#include "sockconnector.h"

SOCK_Connector::SOCK_Connector(void)
{
}

SOCK_Connector::~SOCK_Connector(void)
{
}

void SOCK_Connector::connect( SOCK_Stream &stream, INET_Addr addr )
{
	int status;
	stream.get_handle();
	stream.set_handle( (HANDLE)::socket(PF_INET, SOCK_STREAM, 0) ); // do some error checking!

	status = ::connect( (SOCKET)stream.get_handle(), addr.addr(), addr.size() );
    if (status != 0) 
	{
        fprintf(stderr, "Connect failed.\n");
    }
}