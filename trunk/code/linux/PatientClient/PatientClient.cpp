// reactor_client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "inetaddr.h"
//#include "inetaddr.cpp"
#include "sockacceptor.h"
//#include "sockacceptor.cpp"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "sockstream.h"
//#include "sockstream.cpp"
#include "sockconnector.h"
//#include "sockconnector.cpp"
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>


const short PATIENT_PORT = 10000;

int main(int argc, char* argv[])
{
	char *host;

	std::cout << "Reactor client starting\n";

	/* initialize random seed: */
	srand ( time(NULL) );



	hostent* localHost = gethostbyname("localhost");
	host = inet_ntoa(*(struct in_addr *)*localHost->h_addr_list);
	//u_short port_num = argc > 2 ? atoi ((char *)argv[2]) : LOG_PORT;

	InetAddr patientAddr( PATIENT_PORT,host );
	//InetAddr* address = new InetAddr(PATIENT_PORT,host );
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

