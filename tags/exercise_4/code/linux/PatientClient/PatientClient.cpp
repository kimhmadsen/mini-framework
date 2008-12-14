// reactor_client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include "inetaddr.h"
#include "sockacceptor.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "sockstream.h"
#include "sockconnector.h"
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

using namespace std;

const short PATIENT_PORT = 10000;

int main(int argc, char* argv[])
{
	char *host;
	string run = "run";
	bool running = true;
	int numberOfRequests = 1;
	std::cout << "Reactor client starting\n";

	/* initialize random seed: */
	srand ( time(NULL) );

	if(argc > 1)
	{
			host = (char *)argv[1];
	}
	else
	{
			hostent* localHost = gethostbyname("localhost");
			host = inet_ntoa(*(struct in_addr *)*localHost->h_addr_list);
	}
	if(argc > 2)
	{
		run = (char *)argv[2];
	}
	if(argc > 3)
	{
		numberOfRequests = atoi(argv[3]);
		cout << numberOfRequests << endl;
	}

	InetAddr patientAddr( PATIENT_PORT,host );

	SockStream patientStream;
	SOCK_Connector patientConnector;
	patientConnector.connect (patientStream, patientAddr);
	std::cout << "Patient value stream connected on port " << PATIENT_PORT << " \n";

	int i = 0;
	while(running)
	{
		char buf[256];
		memset(buf, 0, sizeof buf );
		int count;
		cout<< "request " << i << endl;
		if(run.compare("run") == 0)
		{
			std::cout << "Type the cpr number of a patient to get the information: \n";
			std::cin.getline(buf, sizeof buf );
			count = std::cin.gcount();
		}
		else //testing...
		{
			char cpr[] = "090382-3542";
			strcpy(buf, cpr);
			count = strlen(buf);
		}
		patientStream.send_n (buf, count, 0);
		char buf_in[256];
		memset(buf_in, 0, sizeof buf_in );
		count = patientStream.recv(buf_in, sizeof buf_in, 0);
		std::cout << "\n" << buf_in << std::endl;

		i++;

		if(run.compare("run")!= 0 && i == numberOfRequests) //run == "test1" or run == "test2"
			running = false;

		if(run.compare("test2")==0 && running)
		{
			patientConnector.close(patientStream);
			patientConnector.connect (patientStream, patientAddr);
			std::cout << "Patient value stream connected on port " << PATIENT_PORT << " \n";

/*			SockStream patientStream;
			SOCK_Connector patientConnector;
			patientConnector.connect (patientStream, patientAddr);
			std::cout << "Patient value stream connected on port " << PATIENT_PORT << " \n";
*/
		}
	}



	return 0;
}
