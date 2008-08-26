// client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "INET_Addr.h"
#include "SOCK_Stream.h"
#include "SOCK_Connector.h"



const u_short PORT_NUM = 10000;

int _tmain(int argc, _TCHAR* argv[])
{
	
	char buf[BUFSIZ];
	char *host = argc > 1 ? argv[1] : "ics.uci.edu";
	u_short port_num =
		htons (argc > 2 ? atoi (argv[2]) : PORT_NUM);
	INET_Addr server_addr (port_num, host);
	SOCK_Stream cli_stream;
	SOCK_Connector connector;
	// Establish the connection with server.
	connector.connect (cli_stream, server_addr);
	// Send data to server (correctly handles
	// "incomplete writes").
	for (;;) {
		ssize_t r_bytes = read (0, buf, sizeof buf);
		cli_stream.send_n (buf, r_bytes);
	}
	// Explicitly close the connection.
	cli_stream.close ();
	return 0;
}

