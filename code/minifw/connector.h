/**
@file
*/
#pragma once
#include "eventhandler.h"
#include "reactor.h"
#include "sockconnector.h"

/**
Implements the Connector class from POSA2 page 290

Responsibility:
- Actively connects and initializes an associated Service Handler.

Collaborator:
- ServiceHandler
- Dispatcher
- TransportEndPoint
*/
template <class SERVICE_HANDLER>
// The <SERVICE_HANDLER> is the type of concrete
// service handler activated when a connection.
class Connector : public EventHandler
{
public:
	Connector( Reactor* reactor): reactor(reactor){}
	~Connector(void);
private:
	
	SOCK_Connector connector;

	/// Reactor used for asynchronous connection
	/// completion event notifications.
	Reactor* reactor;

	/// Inherited from EventHandler to allow the 
	/// Reactor to notify the Connnector when events 
	/// complete asynchronously
	virtual void HandleEvent(HANDLE handle, Event_Type et );
};
