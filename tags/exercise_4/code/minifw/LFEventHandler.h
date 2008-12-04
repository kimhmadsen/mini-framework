#pragma once
#include "eventhandler.h"
#include "lfthreadpool.h"

class LFEventHandler :
	public EventHandler
{
public:
	LFEventHandler(EventHandler *eh, LFThreadPool *tp);
	~LFEventHandler(void);

	virtual void HandleEvent(HANDLE h, Event_Type et);

private:
	EventHandler *theHandler;
	LFThreadPool *ltp;
};
