#include "StdAfx.h"
#include "selectreactor.h"


Select_Reactor* Select_Reactor::instance_ = 0;

Select_Reactor::Select_Reactor(void)
{
}

Select_Reactor::~Select_Reactor(void)
{
}


Reactor* Select_Reactor::instance(void)
{
	if( instance_ == 0 )
	{
		instance_ = new Select_Reactor();
	}
	return instance_;
}


void Select_Reactor::register_handler(Event_Handler *eh, Event_Type et)
{
}

void Select_Reactor::register_handler(HANDLE h, Event_Handler *eh, Event_Type et)
{
}

void Select_Reactor::remove_handler(Event_Handler *eh, Event_Type et)
{
}

void Select_Reactor::remove_handler(HANDLE h, Event_Type et) const
{
}

void Select_Reactor::handle_events(TIMEVAL *timeout)
{

}
