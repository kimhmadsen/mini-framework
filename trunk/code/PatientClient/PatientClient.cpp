// reactor_client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "inetaddr.h"
#include "sockacceptor.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "SockStream.h"
#include "SockConnector.h"
#include <windows.h>

const short PATIENT_PORT = 10000;

int _tmain(int argc, _TCHAR* argv[])
{
	int i = 0;
	std::cout << "Reactor client starting\n";
	// connect to the server

	//why is that??????? -maria
	WSADATA wsaData;   // if this doesn't work
    //WSAData wsaData; // then try this instead

    if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup failed.\n");
        exit(1);
    }

	/* initialize random seed: */
	srand ( (unsigned int)time(NULL) );


	char *host;
	hostent* localHost = gethostbyname("localhost");
	host = inet_ntoa(*(struct in_addr *)*localHost->h_addr_list);
	//u_short port_num = argc > 2 ? atoi ((char *)argv[2]) : LOG_PORT;


	InetAddr patientAddr( PATIENT_PORT,host );
	SockStream patientStream;
	SOCK_Connector patientConnector;
	patientConnector.connect (patientStream, patientAddr);
	std::cout << "Patient value stream connected on port " << PATIENT_PORT << " \n";
	while(true)
	{
		char buf[256];
		std::cout << "Type the cpr number of a patient to get the information: \n";
		std::cin.getline(buf, sizeof buf );
		int count = std::cin.gcount();

		patientStream.send_n (buf, count, 0);
		char buf_in[256];
		
		count = patientStream.recv(buf_in, sizeof buf_in, 0);
		std::cout << "\n" << buf_in << std::endl;
	}
	
	return 0;
}

