#pragma once
#include "Event_Handler.h"

class ConnectionAcceptor :
	public Event_Handler
{
public:
	ConnectionAcceptor(void);
	~ConnectionAcceptor(void);
};
