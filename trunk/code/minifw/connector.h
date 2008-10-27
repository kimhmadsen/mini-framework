#pragma once
#include "eventhandler.h"
#include "reactor.h"
#include "sockconnector.h"

template <class SERVICE_HANDLER>
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
