#include "ClientEventHandler.h"


using namespace std;

ClientEventHandler::ClientEventHandler()
{

	//Just for local testing
	ClientList *cl = ClientList::Instance();
	cl->Push(this);
	this->reactor = reactor;
	status = false;
	currentPatient = "";
	//isPatientListNew = true; //should be false;
	isPatientListNew = false;
	reactor->RegisterHandler( this, READ_EVENT );
}

ClientEventHandler::ClientEventHandler( const SockStream &stream ): peerStream( stream )
{
	ClientList *cl = ClientList::Instance();
	cl->Push(this);
//	this->reactor = reactor;
	status = false;
	currentPatient = "";
	isPatientListNew = false;
//	reactor->RegisterHandler( this, READ_EVENT );
}


ClientEventHandler::~ClientEventHandler(void)
{
	ClientList *cl = ClientList::Instance();
	cl->Erease(this);
}

void ClientEventHandler::HandleEvent ( HANDLE handle, Event_Type event_type )
{

	switch( event_type )
	{
	case READ_EVENT:
		char input[512];
		int result;
		result = peerStream.recv( input, sizeof(input), 0 );

		if( result > 0 )
		{
			input[result] = '\0';
			switch (input[0])
			{
			case 'G':
				SetPatientList(input,result);
				break;

			case 'P':
				currentPatient.assign(input+2,input+result);
				break;
			case 'S':
				if( strncmp("S started", input, 7 )== 0 )
					status = true;
				else
					status = false;
				break;
			}
		}
		else
		{
			peerStream.close();
			//reactor->RemoveHandler( this, CLOSE_EVENT );
			throw( "Client disconnected\n" );
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

void ClientEventHandler::SetPatientList(char *data, int count)
{
	patientList.clear();
	std::string temp = "";
	int offset = 2;
	int counter = 0;
	while(offset < count)
	{
		temp = "";
		patientList.push_back(temp);
		while(data[offset] != '\n')
		{
			patientList.back() += (data[offset]);
			offset++;
		}
		offset++;

	}

	isPatientListNew = true;

}

std::vector <std::string> ClientEventHandler::GetPatientList()
{
	return patientList;
}

void ClientEventHandler::SetRunning()
{
	if(status)
		peerStream.send("S stop",7,0);
	else
		peerStream.send("S start",7,0);
	//status = !status; //just for local testing
}

void ClientEventHandler::SetRunning(bool desired)
{
	if(desired)
		peerStream.send("S start",7,0);
	else
	peerStream.send("S stop",6,0);

	//status = desired; //just local testing
}

void ClientEventHandler::SelectPatient(std::string data)
{
	int whiteSpace;
	std::string temp ="P ";
	whiteSpace = data.find( " " );

	temp.append(data.substr(0,whiteSpace));
	peerStream.send(temp.c_str(),data.length()+2,0);

	//currentPatient = data; //Just local testing
}

bool ClientEventHandler::IsNewPatientList()
{
	return isPatientListNew;
}

void ClientEventHandler::RequestPatientList()
{
	isPatientListNew = false;
	peerStream.send("G",1,0);
}

std::string ClientEventHandler::GetCurrentPatient(){
	return currentPatient;
}

