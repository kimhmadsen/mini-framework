
#include "LogAcceptor.h"

LogAcceptor::LogAcceptor( InetAddr &addr, Reactor *reactor ):acceptor ( addr ), reactor ( reactor )
{
	this->reactor = reactor;
	reactor->RegisterHandler( this, ACCEPT_EVENT );
}

LogAcceptor::~LogAcceptor(void)
{
	this->reactor->RemoveHandler( this, ACCEPT_EVENT );
}

void LogAcceptor::HandleEvent(HANDLE handle, Event_Type et )
{
	// Can only be called for an ACCEPT event.
	if( et == ACCEPT_EVENT )
	{
		SockStream clientConnection( handle );

		acceptor.accept( clientConnection );

		// create event handlers for the connection.
		LogEventHandler* leh = new LogEventHandler( clientConnection, reactor );

		reactor->RegisterHandler( leh, READ_EVENT );
	}
}

HANDLE LogAcceptor::GetHandle(void)
{
	return acceptor.GetHandle();
}
