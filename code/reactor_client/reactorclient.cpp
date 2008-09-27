// reactor_client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "inetaddr.h"
#include "sockacceptor.h"
#include <stdlib.h>
#include <iostream>
#include "SockStream.h"
#include "SockConnector.h"
#include <windows.h>

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

	InetAddr alarmAddr( ALARM_PORT );
	SockStream alarmStream;
	SOCK_Connector alarmConnector;
	alarmConnector.connect (alarmStream, alarmAddr);

	InetAddr patientAddr( PATVAL_PORT );
	SockStream patientStream;
	SOCK_Connector patientConnector;
	patientConnector.connect (patientStream, patientAddr);

	while(true)
	{
		int i = 0;
		char* bufLog = "I'm sending a log event: " + i;
		//logStream.send_n (bufLog, sizeof(bufLog), 0);
		
		Sleep(2000);

		char* bufAlarm = "alarm, " + i;
		//alarmStream.send_n(bufAlarm, sizeof(bufAlarm), 0);

		Sleep(2000);

		char* bufPat = "1, " + i;
		//patientStream.send_n(bufPat, sizeof(bufPat), 0);

		Sleep(6000);
		i++;
		if(i>20) i = 0;
	}
	
	return 0;
}

