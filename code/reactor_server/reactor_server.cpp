
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
#include "logacceptor.h"
#include "acceptortemplate.h"
#include "alarmeventhandler.h"
#include "patientvalueeventhandler.h"

#define TRACE(x) 

const short LOG_PORT    = 10000;
const short ALARM_PORT  = 10001;
const short PATVAL_PORT = 10002;



int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << "Reactor server starting\n";

	InetAddr log_addr( LOG_PORT );
	InetAddr alarm_addr( ALARM_PORT );
	InetAddr patient_addr( PATVAL_PORT );

	// initialize the frame work 
	MiniFwInit(); 

	// create connection acceptors
	LogAcceptor logAcceptor( log_addr, SelectReactor::instance() );
	AcceptorTemplate<AlarmEventHandler> alarmAcceptor( alarm_addr, SelectReactor::instance() );
	AcceptorTemplate<PatientValueEventHandler> patientValueAcceptor( patient_addr, SelectReactor::instance() );

	// add the acceptors to the reactor
	//SelectReactor::instance()->RegisterHandler( &logAcceptor,          ACCEPT_EVENT );
	//SelectReactor::instance()->RegisterHandler( &alarmAcceptor,        ACCEPT_EVENT );
	//SelectReactor::instance()->RegisterHandler( &patientValueAcceptor, ACCEPT_EVENT );


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

