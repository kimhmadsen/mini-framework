#pragma once

#ifdef WIN32
#include "winsock.h"
#endif

typedef unsigned int Event_Type;

/**
 * Enum definning events for a the event handlers.
 */
enum {
	READ_EVENT    =  1, ///< ACCEPT_EVENT alias READ_EVENT
	ACCEPT_EVENT  =  1,
	WRITE_EVENT   =  2,
	TIMEOUT_EVENT =  4,
	CLOSE_EVENT   =  8, 
};

/**
 * Event handler interface.
 */
class EventHandler
{
public:
	EventHandler(void);
	~EventHandler(void);
	virtual void HandleEvent(HANDLE handle, Event_Type et ) = 0;
	virtual HANDLE GetHandle(void);
private:
	HANDLE handle;
};
