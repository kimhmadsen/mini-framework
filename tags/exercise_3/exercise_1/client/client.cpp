// client.cpp : Defines the entry point for the console application.
//

#include <stdlib.h>
#include <iostream>
#include "stdafx.h"
#include "../net_wrapper/INET_Addr.h"
#include "../net_wrapper/SOCK_Stream.h"
#include "../net_wrapper/SOCK_Connector.h"


const u_short PORT_NUM = 10000;

int _tmain(int argc, _TCHAR* argv[])
{
	
	char buf[BUFSIZ];
	char *host;
	if(argc > 1)
	{
			host = (char *)argv[1];
	}
	else
	{	
			hostent* localHost = gethostbyname("");
			host = inet_ntoa(*(struct in_addr *)*localHost->h_addr_list);
	}
	u_short port_num =
		htons (argc > 2 ? atoi ((char *)argv[2]) : PORT_NUM);
	INET_Addr server_addr (port_num, inet_addr(host));
	SOCK_Stream cli_stream;
	SOCK_Connector connector;
	// Establish the connection with server.
	connector.connect (cli_stream, server_addr);
	// Send data to server (correctly handles
	// "incomplete writes").

	
	for (;;) {
			std::cin.read(buf, sizeof buf);
			int count = std::cin.gcount();
			cli_stream.send_n (buf, count, 0);
	}
	// Explicitly close the connection.
	// it gets closed by the destructor
	//cli_stream.close ();
	return 0;
}

