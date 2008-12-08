#pragma once

#include "eventhandler.h"
#include "sockacceptor.h"
#include "reactor.h"

/**
Implements Acceptor from POSA2 page 290

Responsibility:
- Passively connects and initializes an associated Service Handler

Collaborator:
- ServiceHandler
- Dispatcher
- TransportEndPoint
*/
template <class SERVICE_HANDLER> class Acceptor :
	public EventHandler
{
public:
	Acceptor<SERVICE_HANDLER>( InetAddr &addr, Reactor *reactor ):acceptor(addr), reactor(reactor)
	{
		this->reactor = reactor;
		reactor->RegisterHandler( this, ACCEPT_EVENT );

	};
	
	~Acceptor<SERVICE_HANDLER>(void)
	{
		this->reactor->RemoveHandler( this, ACCEPT_EVENT );
	};
	
	virtual void HandleEvent(HANDLE handle, Event_Type et )
	{
		// Can only be called for an ACCEPT event.
		if( et == ACCEPT_EVENT )
		{
			SockStream clientConnection( handle );

			acceptor.accept( clientConnection );

			// create event handlers for the connection.
			SERVICE_HANDLER* leh = new SERVICE_HANDLER( clientConnection, reactor );
		}
	};
	virtual HANDLE GetHandle(void)
	{
		return acceptor.GetHandle();
	};
private:
	// Socket factory that accepts client connections
	SockAcceptor acceptor;
	// Cached <Reactor>.
	Reactor *reactor;

};


