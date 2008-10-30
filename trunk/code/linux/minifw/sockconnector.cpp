#include "stdafx.h"
#include "sockconnector.h"

SOCK_Connector::SOCK_Connector(void)
{
}

SOCK_Connector::~SOCK_Connector(void)
{
}

void SOCK_Connector::connect( SockStream &stream, InetAddr addr )
{
	int status;

	stream.SetHandle( (HANDLE)::socket(PF_INET, SOCK_STREAM, 0) ); // do some error checking!

	status = ::connect( (SOCKET)stream.GetHandle(), addr.Addr(), addr.Size() );
    if (status != 0)
	{
		//printf("connect failed with error %d\n", WSAGetLastError());
        fprintf(stderr, "Connect failed.\n");
    }
}
void SOCK_Connector::close( SockStream &stream)
{
	stream.close();
}
