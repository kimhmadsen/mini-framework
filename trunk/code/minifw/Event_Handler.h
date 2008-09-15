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

class Event_Handler
{
public:
	Event_Handler(void);
	~Event_Handler(void);
	virtual void handle_event(HANDLE handle, Event_Type et ) = 0;
	virtual SOCKET get_handle(void) = 0;
private:

};
