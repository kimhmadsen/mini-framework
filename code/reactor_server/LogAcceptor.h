#pragma once
#include "eventhandler.h"
#include "reactor.h"
#include "sockacceptor.h"
#include "logeventhandler.h"

class LogAcceptor :
	public EventHandler
{
public:
	LogAcceptor( InetAddr &addr, Reactor *reactor ):
	  acceptor_ ( addr ), reactor_ ( reactor )
	  {
		  reactor_->RegisterHandler( this, ACCEPT_EVENT );
	  }
	~LogAcceptor(void);

	virtual void HandleEvent(HANDLE handle, Event_Type et )
	{
		// Can only be called for an ACCEPT event.
		if( et == ACCEPT_EVENT )
		{
			SockStream client_connection( handle );

			acceptor_.accept( client_connection );

			// create event handlers for the connection.
			LogEventHandler* leh = new LogEventHandler( client_connection, reactor_ );
		}
	}

	virtual HANDLE GetHandle(void)
	{
		return acceptor_.GetHandle();
	}
private:
	// Socket factory that accepts client connections
	SockAcceptor acceptor_;

	// Cached <Reactor>.
	Reactor *reactor_;
};
