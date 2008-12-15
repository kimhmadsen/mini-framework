#pragma once

#include "eventhandler.h"
#include "sockacceptor.h"
#include "reactor.h"

/**
 A standard acceptor templete.
*/
template <class EVENT_HANDLER> class AcceptorTemplate :
	public EventHandler
{
public:
	AcceptorTemplate<EVENT_HANDLER>( InetAddr &addr, Reactor *reactor ):acceptor(addr), reactor(reactor)
	{
		this->reactor = reactor;
		reactor->RegisterHandler( this, ACCEPT_EVENT );

	};
	
	~AcceptorTemplate<EVENT_HANDLER>(void)
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
			EVENT_HANDLER* leh = new EVENT_HANDLER( clientConnection, reactor );
		}
	;}
	virtual HANDLE GetHandle(void)
	{
		return acceptor.GetHandle();
	};
private:
	// Socket factory that accepts client connections
	SockAcceptor acceptor;
	// Cached <Reactor>.
	Reactor *reactor;
	bool isActive;

};


