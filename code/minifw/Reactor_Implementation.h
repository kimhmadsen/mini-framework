#pragma once
#include "event_handler.h"
class Reactor_Implementation
{
public:
	Reactor_Implementation(void);
	~Reactor_Implementation(void);

	virtual void register_handler(Event_Handler *eh, Event_Type et) = 0;
	virtual void register_handler(HANDLE h, Event_Handler *eh, Event_Type et) = 0;
	virtual void remove_handler(Event_Handler *eh, Event_Type et) = 0;
	virtual void remove_handler(HANDLE h, Event_Type et) const = 0;
	
	// Entry point into the reactive event loop
	void handle_events(TIMEVAL *timeout =0);

};
