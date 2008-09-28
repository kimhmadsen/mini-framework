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
	EventTuple *tempEventTuple = new EventTuple();
	tempEventTuple->eventhandler = eh;
	tempEventTuple->eventtype = &et;
	if(!IsEventHandle(tempEventTuple))
		listOfEvents.push_back(tempEventTuple);
}

void SelectReactor::RegisterHandler(HANDLE h, EventHandler *eh, Event_Type et)
{
}

void SelectReactor::RemoveHandler(EventHandler *eh, Event_Type et)
{
	EventTuple *tempEventTuple = new EventTuple();
	tempEventTuple->eventhandler = eh;
	tempEventTuple->eventtype = &et;
	for(unsigned int i = 0; i <listOfEvents.size(); i++)
		if(tempEventTuple->eventhandler == listOfEvents.at(i)->eventhandler && tempEventTuple->eventtype == listOfEvents.at(i)->eventtype)
		{
			EventTuple *memCleanUp = listOfEvents.at(i);
			listOfEvents.erase(listOfEvents.begin()+i);
			delete memCleanUp;
			break;
		}
}

void SelectReactor::RemoveHandler(HANDLE h, Event_Type et) const
{
}

void SelectReactor::HandleEvents(TIMEVAL *timeout)
{

}

bool SelectReactor::IsEventHandle(EventTuple* t)
{
	for(unsigned int i = 0; i <listOfEvents.size(); i++)
	 if(t->eventhandler == listOfEvents.at(i)->eventhandler && t->eventtype == listOfEvents.at(i)->eventtype)
		 return true;
	 else
		 return false;
	return false;
}