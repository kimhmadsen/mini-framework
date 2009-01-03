#pragma once
#include "eventhandler.h"
#include "lfthreadpool.h"


/**
Implements a generic Leader/Followers Event Handler defined by POSA2 page 453

Responsibility:
- Defiens an interface for processing events that occur on a handle

Collaborator:
- Handle
*/
class LFEventHandler :
	public EventHandler
{
public:
	LFEventHandler(EventHandler *eh, LFThreadPool *tp);
	~LFEventHandler(void);

	virtual void HandleEvent(HANDLE h, Event_Type et);

protected:
	EventHandler *theHandler;
	LFThreadPool *ltp;
};
