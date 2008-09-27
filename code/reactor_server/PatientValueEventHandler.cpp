#include <iostream>
#include "PatientValueEventHandler.h"

PatientValueEventHandler::PatientValueEventHandler(const SockStream &stream, Reactor *reactor)
{
}

PatientValueEventHandler::~PatientValueEventHandler(void)
{
}

void PatientValueEventHandler::HandleEvent ( HANDLE handle, Event_Type event_type )
{
	switch( event_type )
	{
	case READ_EVENT:
		char buf[256];
		// code handle short "short-reads" omitted.
		peerStream.recv( buf, sizeof(buf), 0 );

		// Write logging record to standard output
		std::cout << buf;
		break;

	case CLOSE_EVENT:
		peerStream.close();
		reactor->RemoveHandler( this, CLOSE_EVENT );
		break;
	}

}

HANDLE PatientValueEventHandler::GetHandle() 
{
	return peerStream.GetHandle();
}
