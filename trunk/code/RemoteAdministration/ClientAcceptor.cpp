#include "StdAfx.h"
#include "ClientAcceptor.h"
#include "ClientEventHandler.h"

ClientAcceptor::ClientAcceptor( InetAddr &addr, Reactor *reactor, LFThreadPool *tp )
  :LFEventHandler(NULL, tp), acceptor(addr), reactor(reactor)
{

}

ClientAcceptor::~ClientAcceptor(void)
{
}

void ClientAcceptor::HandleEvent(HANDLE handle, Event_Type et)
{
		
	//deactivate the handle.
	ltp->DeactivateHandle( handle, et );

	ltp->PromoteNewLeader();

//	theHandler->HandleEvent(h, et );
	// Can only be called for an ACCEPT event.
	if( et == ACCEPT_EVENT )
	{
		SockStream clientConnection( handle );

		acceptor.accept( clientConnection );

		// create event handlers for the connection.
		ClientEventHandler* leh = new ClientEventHandler( clientConnection );

	}


	//reactivate the handle.
	ltp->ReactivateHandle( handle, et );


}