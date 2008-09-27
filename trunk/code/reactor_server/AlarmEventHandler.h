#pragma once
#include "eventhandler.h"
#include "reactor.h"
#include "sockacceptor.h"

class AlarmEventHandler :
	public EventHandler
{
public:
	AlarmEventHandler(const SockStream &stream, Reactor *reactor);
	~AlarmEventHandler(void);

	virtual void HandleEvent(HANDLE handle, Event_Type et );
	virtual HANDLE GetHandle(void);

private:
	// Receives logging records from a connected client
	SockStream peerStream;
	// Cached <Reactor>.
	Reactor *reactor;
};
