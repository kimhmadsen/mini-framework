#pragma once
#include "winsock.h"
#include "eventhandler.h"


class Reactor
{
public:
	virtual void register_handler(Event_Handler *eh, Event_Type et) = 0;
	virtual void register_handler(HANDLE h, Event_Handler *eh, Event_Type et) = 0;
	virtual void remove_handler(Event_Handler *eh, Event_Type et) = 0;
	virtual void remove_handler(HANDLE h, Event_Type et) const = 0;
	
	// Entry point into the reactive event loop
	virtual void handle_events(TIMEVAL *timeout =0) = 0;
	
	// Define a GoF singleton access point
	static Reactor* instance();
protected:
	Reactor(void){}
	~Reactor(void){}
private:

};
