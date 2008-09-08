// echo_server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "SOCK_Acceptor.h"
#include "SOCK_Stream.h"
#include "INET_Addr.h"

const u_short PORT_NUM = 10000;

int echo_server (u_short port_num)
{
	// Error handling omitted.
	printf( "Echo server listen on port %i\n", port_num );
	INET_Addr my_addr (port_num);
	SOCK_Acceptor acceptor (my_addr);
	SOCK_Stream new_stream;
	acceptor.accept (new_stream);
	for (;;)
	{
		char buf[BUFSIZ];
		
		ssize_t n = new_stream.recv (buf, sizeof buf, 0);
		if( n > 0 )
		{
			std::cout << "Received " << n << " bytes";
			std::cout << buf;
			new_stream.send_n (buf, n, 0);
		}
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	echo_server( PORT_NUM );
	return 0;
}

