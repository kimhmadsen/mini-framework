#include "AlarmEventHandler.h"
#include <string>
#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>

using namespace std;




AlarmEventHandler::AlarmEventHandler(const SockStream &stream, Reactor *reactor): peerStream( stream )
{
	this->reactor = reactor;
	reactor->RegisterHandler( this, READ_EVENT );
}

AlarmEventHandler::~AlarmEventHandler(void)
{
}

bool CompareTime (struct AlarmEvent &ae1, struct AlarmEvent &ae2)
{
	if( ae1.timestamp < ae2.timestamp )
		return true;
	else
		return false;
}

bool ComparePrio (struct AlarmEvent &ae1, struct AlarmEvent &ae2)
{
	if( ae1.prio < ae2.prio )
		return true;
	else 
		return false;
}


void AlarmEventHandler::HandleEvent(HANDLE handle, Event_Type et )
{
	AlarmEvent ae;
	list<AlarmEvent>::iterator p = alarmList.begin();;

	switch( et )
	{
	case READ_EVENT:
		
		char buf[256];
		int result;
		int i;
		// code handle short "short-reads" omitted.
		result = peerStream.recv( buf, sizeof(buf), 0 );
		if( result > 0 )
		{
			buf[result] = '\0';

			std::cout << "New AlarmEvent: " << buf << "\n";
		}
		// save the alarm event in a struct
		time( &ae.timestamp );
		for( i = 0; i<result; i++ )
		{
			if( buf[i] == ',' )
				break;
		}
		ae.prio = atoi( &buf[i+1] );
		strncpy_s(ae.text, sizeof(ae.text), buf, sizeof(buf) );		 
		
		// put the event in a list.

		alarmList.push_front( ae );
		if( alarmList.size() > 10 ) // make sure that only 10 alarms are saved in the list.
		{
			alarmList.sort( CompareTime );
			alarmList.pop_front();
		}

		// display the list.
		alarmList.sort( ComparePrio );
		p = alarmList.begin();

		while( p != alarmList.end() )
		{	
			std::cout << "AlarmEvent " << p->prio << " " << ctime( &p->timestamp ) << " " << p->text << "\n";
			p++;
		}
		
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

