#include "StdAfx.h"
#include "Select_Reactor_Implementation.h"


Select_Reactor_Implementation::Select_Reactor_Implementation(void)
{
}

Select_Reactor_Implementation::~Select_Reactor_Implementation(void)
{
}

void Select_Reactor_Implementation::register_handler(Event_Handler *eh, Event_Type et)
{
}

void Select_Reactor_Implementation::register_handler(HANDLE h, Event_Handler *eh, Event_Type et)
{
}

void Select_Reactor_Implementation::remove_handler(Event_Handler *eh, Event_Type et)
{
}

void Select_Reactor_Implementation::remove_handler(HANDLE h, Event_Type et) const
{
}

void Select_Reactor_Implementation::handle_events(TIMEVAL *timeout )
{
	return;
}
