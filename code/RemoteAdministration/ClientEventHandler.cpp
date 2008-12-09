#include "PatientInfoEventHandler.h"


using namespace std;

ClientEventHandler::ClientEventHandler( const SockStream &stream, Reactor *reactor): peerStream( stream )
{
	this->reactor = reactor;
	status = false;
	currentPatient = "";
	reactor->RegisterHandler( this, READ_EVENT );
}


ClientEventHandler::~ClientEventHandler(void)
{
}

void ClientEventHandler::HandleEvent ( HANDLE handle, Event_Type event_type )
{
	switch( event_type )
	{
	case READ_EVENT:
		char input[256];
		int result;
		result = peerStream.recv( input, sizeof(input), 0 );

		if( result > 0 )
		{
			input[result] = '\0';
			switch (result[0])
			{
			case 'G':
				;
				break;

			case 'P':
				currentPatient.assign(input+2,input+result);
				break;
			case 'S':
				if(result == 7)
					status = true;
				else if(result = 6)
					status = false;
				break;
			}
		}
		break;

	case CLOSE_EVENT:
		peerStream.close();
		reactor->RemoveHandler( this, CLOSE_EVENT );
		break;
	}

}

HANDLE ClientEventHandler::GetHandle() 
{
	return peerStream.GetHandle();
}

bool ClientEventHandler::IsRunning()
{
	return status;
}