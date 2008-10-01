#include "StdAfx.h"
#include "selectreactor.h"


SelectReactor* SelectReactor::instance_ = 0;

SelectReactor::SelectReactor(void)
{
	sed = new SynchEventDemux();
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
	EventTuple *tempEventTupleVector = new EventTuple();
	tempEventTupleVector->eventhandler = eh;
	tempEventTupleVector->eventtype = et;
	if(!IsEventHandle(tempEventTupleVector))
		listOfEvents.push_back(tempEventTupleVector);
}

void SelectReactor::RegisterHandler(HANDLE h, EventHandler *eh, Event_Type et)
{
}

void SelectReactor::RemoveHandler(EventHandler *eh, Event_Type et)
{
	EventTuple *tempEventTupleVector = new EventTuple();
	tempEventTupleVector->eventhandler = eh;
	tempEventTupleVector->eventtype = et;
	for(unsigned int i = 0; i <listOfEvents.size(); i++)
		if(tempEventTupleVector->eventhandler == listOfEvents.at(i)->eventhandler && tempEventTupleVector->eventtype == listOfEvents.at(i)->eventtype)
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
	ConvertFDsToSets(readFDs,writeFDs, exceptFDs);
	int handleMaximum = FD_SETSIZE;
	int result = sed->select( handleMaximum, &readFDs, &writeFDs, &exceptFDs, timeout);
	if(result == SOCKET_ERROR)
		printf("ERROR: %d\n", WSAGetLastError()); // comment out if porting, WSAGetLastError is winsock.h
	else if (result == 0) 
		printf("No result\n"); // Timeout errors perhaps?
	else 
	{	
		std::vector<EventTuple*> *tempEventTupleVector = new std::vector<EventTuple*>;
		std::vector<EventTuple*>::iterator iteration = listOfEvents.begin();
		while(iteration != listOfEvents.end()) 
		{
			EventTuple *tuple = new EventTuple();
			tuple->eventhandler = (*iteration)->eventhandler;
			tuple->eventtype = (*iteration)->eventtype;
			tempEventTupleVector->push_back(tuple);
			iteration++;
		}
		for (int i = 0; i <= handleMaximum-1 && result > 0 && i < tempEventTupleVector->size(); i++) 
		{
			EventHandler *handlerUpcoming = tempEventTupleVector->at(i)->eventhandler;
			HANDLE handle = handlerUpcoming->GetHandle();
			if (FD_ISSET(handle, &readFDs) ) 
			{
				handlerUpcoming->HandleEvent(handle, READ_EVENT);
				result--;
			} 
			else if (FD_ISSET(handle, &writeFDs) ) 
			{
				handlerUpcoming->HandleEvent(handle, WRITE_EVENT);
				result--;
			} 
			else if (FD_ISSET(handle, &exceptFDs) ) 
			{
				result--;
			}
				
		}

		//Memory clean-up
		std::vector<EventTuple*>::iterator iterationMore = tempEventTupleVector->begin();
		while(iterationMore != tempEventTupleVector->end()) {
			EventTuple *temp = *iterationMore++;
			delete temp;
		}
		tempEventTupleVector->clear();
	}

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

void SelectReactor::ConvertFDsToSets(fd_set &readFDs, fd_set &writeFDs, fd_set &exceptFDs)
{

	FD_ZERO(&readFDs);
	FD_ZERO(&writeFDs);
	FD_ZERO(&exceptFDs);
	for (unsigned int i = 0; i < listOfEvents.size(); i++) 
	{
		if(listOfEvents.at(i)->eventtype == READ_EVENT)
			FD_SET((SOCKET)listOfEvents.at(i)->eventhandler->GetHandle(), &readFDs);
		else if  (listOfEvents.at(i)->eventtype == WRITE_EVENT)
			FD_SET((SOCKET)listOfEvents.at(i)->eventhandler->GetHandle(), &writeFDs);
		else if  (listOfEvents.at(i)->eventtype == TIMEOUT_EVENT)
			FD_SET((SOCKET)listOfEvents.at(i)->eventhandler->GetHandle(), &exceptFDs);
	}

}