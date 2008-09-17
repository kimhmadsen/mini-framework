#include "StdAfx.h"
#include "Select_Reactor.h"

Select_Reactor* Select_Reactor::instance_ = 0;

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


Select_Reactor::~Select_Reactor(void)
{
}
