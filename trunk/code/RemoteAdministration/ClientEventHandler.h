#pragma once
#include <vector>
#include <list>
#include <iostream>
#include <string>
#include "eventhandler.h"
#include "reactor.h"
#include "sockacceptor.h"
#include "PatientDBReader.h"

class ClientEventHandler :
	public EventHandler
{
public:
	ClientEventHandler( const SockStream &stream, Reactor *reactor);
	~ClientEventHandler(void);

	virtual void HandleEvent ( HANDLE handle, Event_Type event_type );
	virtual HANDLE GetHandle();
private:
	// Receives logging records from a connected client
	SockStream peerStream;
		// Cached <Reactor>.
	Reactor *reactor;
	PatientDBReader *dbReader;

};

