#pragma once
#include "reactor.h"


class SelectReactor :
	public Reactor
{
public:
	virtual void RegisterHandler(EventHandler *eh, Event_Type et);
	virtual void RegisterHandler(HANDLE h, EventHandler *eh, Event_Type et);
	virtual void RemoveHandler(EventHandler *eh, Event_Type et);
	virtual void RemoveHandler(HANDLE h, Event_Type et) const;
	void HandleEvents(TIMEVAL *timeout =0);

	static Reactor* instance(void);
protected:
	SelectReactor(void);
	~SelectReactor(void);

private:

	static SelectReactor* instance_;
};
