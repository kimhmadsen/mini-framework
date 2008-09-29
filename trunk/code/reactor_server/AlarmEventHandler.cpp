#include "AlarmEventHandler.h"
#include <string>
#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

struct AlarmEvent
{
	int prio;
	string text;
	time_t timestamp;
};



AlarmEventHandler::AlarmEventHandler(const SockStream &stream, Reactor *reactor): peerStream( stream )
{
	this->reactor = reactor;
	reactor->RegisterHandler( this, READ_EVENT );
}

AlarmEventHandler::~AlarmEventHandler(void)
{
}


void AlarmEventHandler::HandleEvent(HANDLE handle, Event_Type et )
{
	switch( et )
	{
	case READ_EVENT:
		char buf[256];
		// code handle short "short-reads" omitted.
		peerStream.recv( buf, sizeof(buf), 0 );

		// Write logging record to standard output
		// @todo:
		std::cout << buf;
		break;

	case CLOSE_EVENT:
		peerStream.close();
		reactor->RemoveHandler( this, CLOSE_EVENT );
		break;
	}
}

HANDLE AlarmEventHandler::GetHandle(void)
{
	return peerStream.GetHandle();
}

