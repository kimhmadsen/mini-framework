#pragma once
#include "winsock.h"
#include "event_handler.h"
#include "reactor_implementation.h"
#include "select_reactor_implementation.h"
class Reactor
{
public:
	virtual void register_handler(Event_Handler *eh, Event_Type et) = 0;
	virtual void register_handler(HANDLE h, Event_Handler *eh, Event_Type et) = 0;
	virtual void remove_handler(Event_Handler *eh, Event_Type et) = 0;
	virtual void remove_handler(HANDLE h, Event_Type et) const = 0;
	
	// Entry point into the reactive event loop
	void handle_events(TIMEVAL *timeout =0);
	
	// Define a GoF singleton access point
	static Reactor* instance()
	{
		if( instance_ == 0 )
		{
			instance_ = new Reactor();
		}
		return instance_;
	}
protected:
	Reactor(void);
	~Reactor(void);
private:
	static Reactor* instance_;
	// Use the Bridge pattern to hold a pointer to 
	// the <Reactor_Implementation>.
	Reactor_Implementation* reactor_impl_; // Uses the Bridge pattern
};
