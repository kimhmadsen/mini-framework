// reactor_server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "INET_Addr.h"
#include "Reactor.h"

const short LOG_PORT    = 10000;
const short ALARM_PORT  = 10001;
const short PATVAL_PORT = 10002;


int _tmain(int argc, _TCHAR* argv[])
{
	INET_Addr log_addr( LOG_PORT );
	INET_Addr alarm_addr( ALARM_PORT );
	INET_Addr parient_addr( PATVAL_PORT );

	// create connection acceptors


	// add the acceptors to the reactor


	// do the server loop
	for(;;)
	{
		TIMEVAL tv;
		tv.tv_sec  = 0;
		tv.tv_usec = 100000;
		Reactor::instance()->handle_events( &tv );
		// do timeout things 
	}

	return 0;
}

