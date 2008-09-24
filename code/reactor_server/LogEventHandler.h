#pragma once
#include "iostream"
#include "eventhandler.h"
#include "reactor.h"
#include "sockstream.h"

class LogEventHandler :
	public EventHandler
{
public:
	LogEventHandler(const SockStream &stream, Reactor *reactor);
	~LogEventHandler(void);

	virtual void HandleEvent ( HANDLE handle, Event_Type event_type );
	virtual HANDLE GetHandle();
private:
	// Receives logging records from a connected client
	SockStream peerStream;
		// Cached <Reactor>.
	Reactor *reactor;

};
