/**
 *
 */
#include <iostream>
#include "PatientValueEventHandler.h"

PatientValueEventHandler::PatientValueEventHandler(const SockStream &stream, Reactor *reactor): peerStream( stream )
{
	this->reactor = reactor;
	reactor->RegisterHandler( this, READ_EVENT );
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
		int result;
		// code handle short "short-reads" omitted.
		result = peerStream.recv( buf, sizeof(buf), 0 );

		if( result > 0 )
		{
			buf[result] = '\0';

			// Write logging record to standard output
			std::cout << "PatientValueEvent: " << buf << "\n";
		}
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
