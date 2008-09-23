// echo_server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "SockAcceptor.h"
#include "SockStream.h"
#include "InetAddr.h"

const u_short PORT_NUM = 10000;

int echo_server (u_short port_num)
{
	// Error handling omitted.
	printf( "Echo server listen on port %i\n", port_num );
	WSADATA wsaData;   // if this doesn't work
    //WSAData wsaData; // then try this instead

    if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup failed.\n");
        exit(1);
    }

	InetAddr my_addr (port_num);
	SockAcceptor acceptor (my_addr);
	SockStream new_stream;
	acceptor.accept (new_stream);
	for (;;)
	{
		char buf[BUFSIZ];
		
		ssize_t n = new_stream.recv (buf, sizeof buf, 0);
		if( n > 0 )
		{
			std::cout << "Received " << n << " bytes ";
			std::cout << buf << "\n";
			new_stream.send_n (buf, n, 0);
		}
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	echo_server( PORT_NUM );
	return 0;
}

