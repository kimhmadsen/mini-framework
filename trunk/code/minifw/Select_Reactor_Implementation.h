#pragma once
#include "reactor_implementation.h"

class Select_Reactor_Implementation :
	public Reactor_Implementation
{
public:
	Select_Reactor_Implementation(void);
	~Select_Reactor_Implementation(void);
	virtual void register_handler(Event_Handler *eh, Event_Type et);
	virtual void register_handler(HANDLE h, Event_Handler *eh, Event_Type et);
	virtual void remove_handler(Event_Handler *eh, Event_Type et);
	virtual void remove_handler(HANDLE h, Event_Type et) const;
	
	// Entry point into the reactive event loop
	void handle_events(TIMEVAL *timeout =0);
};
