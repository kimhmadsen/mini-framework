// reactor_server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "inetaddr.h"
#include "reactor.h"
#include "selectreactor.h"
#include "logacceptor.h"

#define TRACE(x) (x)

const short LOG_PORT    = 10000;
const short ALARM_PORT  = 10001;
const short PATVAL_PORT = 10002;



int _tmain(int argc, _TCHAR* argv[])
{
	InetAddr log_addr( LOG_PORT );
	InetAddr alarm_addr( ALARM_PORT );
	InetAddr parient_addr( PATVAL_PORT );

	// create connection acceptors
	LogAcceptor la( log_addr, SelectReactor::instance() );

	// add the acceptors to the reactor
	SelectReactor::instance()->RegisterHandler( &la, ACCEPT_EVENT );


	// do the server loop
	for(;;)
	{
		TIMEVAL tv;
		tv.tv_sec  = 0;
		tv.tv_usec = 100000;
		SelectReactor::instance()->HandleEvents( &tv );
		// do timeout things 
		TRACE( printf( "." ) );
	}

	return 0;
}

