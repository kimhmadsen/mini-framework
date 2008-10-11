#pragma once
#include "EventHandler.h"
#include "sockstream.h"
#include "reactor.h"

class PatientValueEventHandler :
	public EventHandler
{
public:
	PatientValueEventHandler(const SockStream &stream, Reactor *reactor);
	~PatientValueEventHandler(void);

	virtual void HandleEvent ( HANDLE handle, Event_Type event_type );
	virtual HANDLE GetHandle();
private:
	// Receives logging records from a connected client
	SockStream peerStream;
		// Cached <Reactor>.
	Reactor *reactor;
};
