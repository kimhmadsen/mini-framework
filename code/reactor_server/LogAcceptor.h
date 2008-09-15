#pragma once
#include "Event_Handler.h"
#include "Reactor.h"
#include "SOCK_Acceptor.h"
#include "LogEventHandler.h"

class LogAcceptor :
	public Event_Handler
{
public:
	LogAcceptor( INET_Addr &addr, Reactor *reactor ):
	  acceptor_ ( addr ), reactor_ ( reactor )
	  {
		  reactor_->register_handler( this, ACCEPT_EVENT );
	  }
	~LogAcceptor(void);

	virtual void handle_event(HANDLE handle, Event_Type et )
	{
		// Can only be called for an ACCEPT event.
		if( et == ACCEPT_EVENT )
		{
			SOCK_Stream client_connection;

			acceptor_.accept( client_connection );

			// create event handlers for the connection.
			LogEventHandler* leh = new LogEventHandler( client_connection, Reactor::instance() );
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
