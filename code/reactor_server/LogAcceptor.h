#pragma once
#include "Event_Handler.h"
#include "Reactor.h"
#include "SOCK_Acceptor.h"

class ConnectionAcceptor :
	public Event_Handler
{
public:
	ConnectionAcceptor( INET_Addr &addr, Reactor *reactor ):
	  acceptor_ ( addr ), reactor_ ( reactor )
	  {
		  reactor_->register_handler( this, ACCEPT_EVENT );
	  }
	~ConnectionAcceptor(void);

	virtual void handle_event(HANDLE handle, Event_Type et )
	{
		// Can only be called for an ACCEPT event.
		if( et == ACCEPT_EVENT )
		{
			SOCK_Stream client_connection;

			acceptor_.accept( client_connection );

			// create event handlers for the connection.

		}
	}
	virtual SOCKET get_handle(void)
	{
		return acceptor_.get_handle();
	}
private:
	// Socket factory that accepts client connections
	SOCK_Acceptor acceptor_;

	// Cached <Reactor>.
	Reactor *reactor_;
};
