#include "PatientInfoEventHandler.h"


using namespace std;

PatientInfoEventHandler::PatientInfoEventHandler( const SockStream &stream, Reactor *reactor): peerStream( stream )
{
	this->reactor = reactor;
	reactor->RegisterHandler( this, READ_EVENT );
	dbReader->setDBFile( "PatientDB.txt");
}


PatientInfoEventHandler::~PatientInfoEventHandler(void)
{
}

void PatientInfoEventHandler::HandleEvent ( HANDLE handle, Event_Type event_type )
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
			string info = dbReader->getPatient(buf);
			std::cout << "Patient info: " << info  << "\n";
		}
		break;

	case CLOSE_EVENT:
		peerStream.close();
		reactor->RemoveHandler( this, CLOSE_EVENT );
		break;
	}


	//TODO: do something... read file and return info
}

HANDLE PatientInfoEventHandler::GetHandle() 
{
	return peerStream.GetHandle();
}

