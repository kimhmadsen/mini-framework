#pragma once

#include "winsock.h"
//typedef unsigned int HANDLE;
typedef unsigned int Event_Type;
enum {
	READ_EVENT    = 01, // ACCEPT_EVENT alias READ_EVENT
	ACCEPT_EVENT  = 01,
	WRITE_EVENT   = 02,
	TIMEOUT_EVENT = 04,
	CLOSE_EVENT   =  8, 
};

class EventHandler
{
public:
	EventHandler(void);
	~EventHandler(void);
	virtual void HandleEvent(HANDLE handle, Event_Type et ) = 0;
	virtual HANDLE GetHandle(void) = 0;
private:

};
