#pragma once
#include "reactor.h"


class Select_Reactor :
	public Reactor
{
public:
	virtual void register_handler(Event_Handler *eh, Event_Type et);
	virtual void register_handler(HANDLE h, Event_Handler *eh, Event_Type et);
	virtual void remove_handler(Event_Handler *eh, Event_Type et);
	virtual void remove_handler(HANDLE h, Event_Type et) const;
	void handle_events(TIMEVAL *timeout =0);

	static Reactor* instance(void);
protected:
	Select_Reactor(void);
	~Select_Reactor(void);

private:

	static Select_Reactor* instance_;
};
