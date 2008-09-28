#pragma once
#include "reactor.h"
#include <vector>
#include <iterator>
#include <stdlib.h>

class SelectReactor :
	public Reactor
{
public:

	struct EventTuple
	{
		EventHandler *eventhandler;
		Event_Type *eventtype;
	};
	virtual void RegisterHandler(EventHandler *eh, Event_Type et);
	virtual void RegisterHandler(HANDLE h, EventHandler *eh, Event_Type et);
	virtual void RemoveHandler(EventHandler *eh, Event_Type et);
	virtual void RemoveHandler(HANDLE h, Event_Type et) const;
	bool IsEventHandle(EventTuple *);
	void HandleEvents(TIMEVAL *timeout =0);
	static Reactor* instance(void);
protected:
	SelectReactor(void);
	~SelectReactor(void);

private:
	std::vector<EventTuple*> listOfEvents;
	static SelectReactor* instance_;
};
