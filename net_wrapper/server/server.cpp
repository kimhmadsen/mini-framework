// server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SOCK_Acceptor.h"
#include "SOCK_Stream.h"
#include "INET_Addr.h"

const u_short PORT_NUM = 10000;

int echo_server (u_short port_num)
{
	// Error handling omitted.
	INET_Addr my_addr (port_num);
	SOCK_Acceptor acceptor (my_addr);
	SOCK_Stream new_stream;
	acceptor.accept (new_stream);
	for (;;)
	{
		char buf[BUFSIZ];
		// Error caught at compile time!
		ssize_t n = acceptor.recv (buf, sizeof buf);
		new_stream.send_n (buf, n);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	echo_server(PORT_NUM);
	return 0;
}

