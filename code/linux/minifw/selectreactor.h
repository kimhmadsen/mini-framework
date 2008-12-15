#pragma once
#include "reactor.h"
#include "syncheventdemux.h"
#include <vector>
#include <iterator>
#include <stdlib.h>
#include <sys/socket.h>

#define SOCKET_ERROR -1
typedef int SOCKET;

/**
Implements the Reactor interface using the function select.
*/
class SelectReactor :
	public Reactor
{
public:

	/**
		Structure for holding tuples of eventer handler and eventtype.
	*/
	struct EventTuple
	{
		EventHandler *eventhandler;
		Event_Type eventtype;
	};
	virtual void RegisterHandler(EventHandler *eh, Event_Type et);
	virtual void RegisterHandler(HANDLE h, EventHandler *eh, Event_Type et);
	virtual void RemoveHandler(EventHandler *eh, Event_Type et);
	virtual void RemoveHandler(HANDLE h, Event_Type et) const;
	void ConvertFDsToSets(fd_set &readFDs, fd_set &writeFDs, fd_set &exceptFDs);
	bool IsEventHandle(EventTuple *);
	void HandleEvents(struct timeval *timeout =0);
	static Reactor* instance(void);
protected:
	SelectReactor(void);
	~SelectReactor(void);

private:
	std::vector<EventTuple*> listOfEvents;
	static SelectReactor* instance_;
	fd_set readFDs, writeFDs, exceptFDs;
	SynchEventDemux *sed;
};
