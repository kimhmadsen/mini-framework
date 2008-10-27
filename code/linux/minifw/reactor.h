#pragma once
#include "winsock.h"
#include "eventhandler.h"

/**
The Reactor class.
Responsibility:
- Registers and removes event handlers and their associated handles
- Manages a handle set
- Runs the application's event loop
*/
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
