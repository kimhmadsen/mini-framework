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

const short LOG_PORT    = 10000;
const short ALARM_PORT  = 10001;
const short PATVAL_PORT = 10002;


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
	srand ( (unsigned int) time(NULL) );


	char *host;
	hostent* localHost = gethostbyname("localhost");
	host = inet_ntoa(*(struct in_addr *)*localHost->h_addr_list);
	//u_short port_num = argc > 2 ? atoi ((char *)argv[2]) : LOG_PORT;

	InetAddr logAddr(LOG_PORT, host );//( LOG_PORT );
	SockStream logStream;
	SOCK_Connector logConnector;
	logConnector.connect (logStream, logAddr);
	std::cout << "Log stream connected on port " << LOG_PORT << " \n";

	InetAddr alarmAddr( ALARM_PORT,host );
	SockStream alarmStream;
	SOCK_Connector alarmConnector;
	alarmConnector.connect (alarmStream, alarmAddr);
	std::cout << "Alarm stream connected on port " << ALARM_PORT << " \n";

	InetAddr patientAddr( PATVAL_PORT,host );
	SockStream patientStream;
	SOCK_Connector patientConnector;
	patientConnector.connect (patientStream, patientAddr);
	std::cout << "Patient value stream connected on port " << PATVAL_PORT << " \n";
	while(true)
	{
		int ran;
		char buf[256];
		sprintf(buf, "I'm sending a log event: %d", i);
		logStream.send_n (buf, strlen(buf), 0);

		Sleep(2000);

		//char bufAlarm[] = "alarm, " + i;
		ran = rand() % 10; // random numer from 0 to 9,
		sprintf(buf, "alarm, %d", ran);
		alarmStream.send_n(buf, strlen(buf), 0);

		Sleep(2000);

		//char bufPat[] = "1, " + i;
		sprintf(buf, "1,  %d", i);
		patientStream.send_n(buf, strlen(buf), 0);

		Sleep(6000);
		i++;
		if(i>20) i = 0;
	}
	
	return 0;
}

