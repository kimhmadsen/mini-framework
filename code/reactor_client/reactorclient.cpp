// reactor_client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "inetaddr.h"
#include "sockacceptor.h"
#include <stdlib.h>
#include <iostream>
#include "SockStream.h"
#include "SockConnector.h"

const short LOG_PORT    = 10000;
const short ALARM_PORT  = 10001;
const short PATVAL_PORT = 10002;


int _tmain(int argc, _TCHAR* argv[])
{
	// connect to the server

	//why is that??????? -maria
	WSADATA wsaData;   // if this doesn't work
    //WSAData wsaData; // then try this instead

    if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup failed.\n");
        exit(1);
    }

	InetAddr logAddr( LOG_PORT );
	SockStream logStream;
	SOCK_Connector logConnector;
	logConnector.connect (logStream, logAddr);
	char buf[] = "I'm sending a log event";
	logStream.send_n (buf, sizeof(buf), 0);

	InetAddr alarmAddr( ALARM_PORT );
	SockStream alarmStream;
	SOCK_Connector alarmConnector;
	alarmConnector.connect (alarmStream, alarmAddr);

	InetAddr patientAddr( PATVAL_PORT );
	SockStream patientStream;
	SOCK_Connector patientConnector;
	patientConnector.connect (patientStream, patientAddr);


	// send some events
	// Log events ( a string )
	// Patient value events ( type and value field )
	// Alarm events ( priorit field and value field )	
	//for (;;) {
	//	std::cin.getline(buf, sizeof buf );//.read(buf, sizeof buf);
	//	int count = std::cin.gcount();

	//	cli_stream.send_n (buf, count, 0);
	//}
	
	// Explicitly close the connection.
	// it gets closed by the destructor
	//cli_stream.close ();
	return 0;
}

