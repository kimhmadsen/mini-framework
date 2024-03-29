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
	ACCEPT_EVENT  =  1, ///< Accept event
	WRITE_EVENT   =  2, ///< Write event
	TIMEOUT_EVENT =  4, ///< Timeout event 
	CLOSE_EVENT   =  8, ///< Close event
};

/**
Event handler used as an abstract class.
Responsibility:
- Defines an interface for processing indication event tht occur on a handle.

Collaborator:
- Handle
 */
class EventHandler
{
public:
	EventHandler(void);
	virtual ~EventHandler(void);
	virtual void HandleEvent(HANDLE handle, Event_Type et ) = 0;
	virtual HANDLE GetHandle(void);
	virtual void SetHandle(HANDLE handle);
private:
	HANDLE handle;
};
