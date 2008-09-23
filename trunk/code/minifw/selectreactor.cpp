#include "StdAfx.h"
#include "selectreactor.h"


SelectReactor* SelectReactor::instance_ = 0;

SelectReactor::SelectReactor(void)
{
}

SelectReactor::~SelectReactor(void)
{
}


Reactor* SelectReactor::instance(void)
{
	if( instance_ == 0 )
	{
		instance_ = new SelectReactor();
	}
	return instance_;
}


void SelectReactor::RegisterHandler(EventHandler *eh, Event_Type et)
{
}

void SelectReactor::RegisterHandler(HANDLE h, EventHandler *eh, Event_Type et)
{
}

void SelectReactor::RemoveHandler(EventHandler *eh, Event_Type et)
{
}

void SelectReactor::RemoveHandler(HANDLE h, Event_Type et) const
{
}

void SelectReactor::HandleEvents(TIMEVAL *timeout)
{

}
