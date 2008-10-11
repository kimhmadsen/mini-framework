#pragma once
#include "winsock.h"
#include "eventhandler.h"


class Reactor
{
public:
	virtual void RegisterHandler(EventHandler *eh, Event_Type et) = 0;
	virtual void RegisterHandler(HANDLE h, EventHandler *eh, Event_Type et) = 0;
	virtual void RemoveHandler(EventHandler *eh, Event_Type et) = 0;
	virtual void RemoveHandler(HANDLE h, Event_Type et) const = 0;
	
	// Entry point into the reactive event loop
	virtual void HandleEvents(TIMEVAL *timeout =0) = 0;
	
	// Define a GoF singleton access point
	static Reactor* instance();
protected:
	Reactor(void){}
	~Reactor(void){}
private:

};
