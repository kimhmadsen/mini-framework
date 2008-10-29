// PatientServer.cpp : Defines the entry point for the console application.
//

/**
 * The server application shall handle the following events:
 * - an alarm event (carrying a priority field and a text string)
 * - a patient value event (carrying a type field and a value field)
 * - a log event (carrying a text string)
 *
 * 
 * Each time an alarm is received the application shall display the last 10 alarms on the screen in priority order with a time stamp.
 * The received patient values are displayed as they are received.
 * Received log events are displayed as the are received (in real life: should be stored on a log file).
 *
 */

#include "stdafx.h"
#include "minifw.h"
#include "inetaddr.h"
#include "reactor.h"
#include "selectreactor.h"
#include "acceptortemplate.h"
#include "patientinfoeventhandler.h"


#define TRACE(x) 

const short PATIENT_PORT = 10000;



int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << "Reactor server starting\n";

	InetAddr patient_addr( PATIENT_PORT );

	// initialize the frame work 
	MiniFwInit(); 

	// create connection acceptors
	AcceptorTemplate<PatientInfoEventHandler> patientInfoAcceptor( patient_addr, SelectReactor::instance() );
	std::cout << "Patient info acceptor listen on port " << patient_addr.GetPort() << "\n";

	// do the server loop
	for(;;)
	{
		TIMEVAL tv;
		tv.tv_sec  = 10;
		tv.tv_usec = 100000;
		SelectReactor::instance()->HandleEvents( &tv );
		// do timeout things 
		TRACE( printf( "." ) );
	}

	return 0;
}

