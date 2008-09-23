// echo_client.cpp : Defines the entry point for the console application.
//

#include <stdlib.h>
#include <iostream>
#include "stdafx.h"
#include "InetAddr.h"
#include "SockStream.h"
#include "SockConnector.h"


const u_short PORT_NUM = 10000;

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsaData;   // if this doesn't work
    //WSAData wsaData; // then try this instead

    if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup failed.\n");
        exit(1);
    }

	char buf[BUFSIZ];
	char *host;
	if(argc > 1)
	{
			host = (char *)argv[1];
	}
	else
	{	
			hostent* localHost = gethostbyname("localhost");
			host = inet_ntoa(*(struct in_addr *)*localHost->h_addr_list);
	}
	u_short port_num = argc > 2 ? atoi ((char *)argv[2]) : PORT_NUM;
	
	InetAddr server_addr (port_num, host );
	SockStream cli_stream;
	SOCK_Connector connector;
	// Establish the connection with server.
	connector.connect (cli_stream, server_addr);
	// Send data to server (correctly handles
	// "incomplete writes").

	
	for (;;) {
		std::cin.getline(buf, sizeof buf );//.read(buf, sizeof buf);
		int count = std::cin.gcount();

		cli_stream.send_n (buf, count, 0);
	}
	// Explicitly close the connection.
	// it gets closed by the destructor
	//cli_stream.close ();
	return 0;
}

