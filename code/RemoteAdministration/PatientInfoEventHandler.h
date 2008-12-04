#pragma once
#include <vector>
#include <list>
#include <iostream>
#include <string>
#include "eventhandler.h"
#include "reactor.h"
#include "sockacceptor.h"
#include "PatientDBReader.h"

class PatientInfoEventHandler :
	public EventHandler
{
public:
	PatientInfoEventHandler( const SockStream &stream, Reactor *reactor);
	~PatientInfoEventHandler(void);

	virtual void HandleEvent ( HANDLE handle, Event_Type event_type );
	virtual HANDLE GetHandle();
private:
	// Receives logging records from a connected client
	SockStream peerStream;
		// Cached <Reactor>.
	Reactor *reactor;
	PatientDBReader *dbReader;

};

