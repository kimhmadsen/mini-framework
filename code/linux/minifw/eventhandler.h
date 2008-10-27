#pragma once
#include <sys/socket.h>
typedef unsigned int Event_Type;
typedef int HANDLE;

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
	~EventHandler(void);
	virtual void HandleEvent(HANDLE handle, Event_Type et ) = 0;
	virtual HANDLE GetHandle(void);
private:
	HANDLE handle;
};
