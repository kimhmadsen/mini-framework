#pragma once
#include "eventhandler.h"
#include "sockstream.h"

/**
Service handler for socket connection.
Responsibility:
- Implementats a half of an end-to-end servie in a networked application.

Collaborator
- Dispatcher eg. Reactor
- Transport Endpoint
*/
class ServiceHandler :
	public EventHandler
{
public:
	ServiceHandler(void);
	~ServiceHandler(void);
	virtual void open() = 0;
	SockStream &peer();

};
