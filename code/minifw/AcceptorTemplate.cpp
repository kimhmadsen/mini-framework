#include "stdafx.h"
#include "AcceptorTemplate.h"

//template <class EVENT_HANDLER> AcceptorTemplate<EVENT_HANDLER>::AcceptorTemplate( InetAddr &addr, Reactor *reactor ):acceptor ( addr ), reactor ( reactor )
//{
//	this->reactor = reactor;
//	reactor->RegisterHandler( this, ACCEPT_EVENT );
//
//}

//template <class EVENT_HANDLER>AcceptorTemplate<EVENT_HANDLER>::~AcceptorTemplate(void)
//{
//	this->reactor->RemoveHandler( this, ACCEPT_EVENT );
//}


//template <class EVENT_HANDLER> void AcceptorTemplate<EVENT_HANDLER>::HandleEvent(HANDLE handle, Event_Type et )
//{
//	// Can only be called for an ACCEPT event.
//	if( et == ACCEPT_EVENT )
//	{
//		SockStream clientConnection( handle );
//
//		acceptor.accept( clientConnection );
//
//		// create event handlers for the connection.
//		EVENT_HANDLER* leh = new EVENT_HANDLER( clientConnection, reactor );
//
//		reactor->RegisterHandler( leh, READ_EVENT );
//	}
//}
//
//template <class EVENT_HANDLER> HANDLE AcceptorTemplate<EVENT_HANDLER>::GetHandle(void)
//{
//	return acceptor.GetHandle();
//}

