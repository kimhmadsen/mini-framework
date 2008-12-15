#pragma once

#include "eventhandler.h"
#include "sockacceptor.h"
#include "reactor.h"
#include "LFThreadPool.h"
#include "LFEventHandler.h"

template <class EVENT_HANDLER> class LFAcceptor  :
	public EventHandler
{
public:
	LFAcceptor<EVENT_HANDLER>( InetAddr &addr, Reactor *reactor, LFThreadPool* ltp  ):acceptor(addr), reactor(reactor)
	{
		this->reactor = reactor;
		reactor->RegisterHandler( this, ACCEPT_EVENT );
		this->ltp = ltp;
	};
	
	~LFAcceptor<EVENT_HANDLER>(void)
	{
		this->reactor->RemoveHandler( this, ACCEPT_EVENT );
	};
	
	virtual void HandleEvent(HANDLE handle, Event_Type et )
	{

		//deactivate the handle.
//		ltp->DeactivateHandle( handle, et );

//		ltp->PromoteNewLeader();

		// Handle the event
		//theHandler->HandleEvent(h, et );
		// Can only be called for an ACCEPT event.
		if( et == ACCEPT_EVENT )
		{
			SockStream clientConnection( handle );

			acceptor.accept( clientConnection );

			// create event handlers for the connection.
			EVENT_HANDLER* leh = new EVENT_HANDLER( clientConnection );
			LFEventHandler* lfeh = new LFEventHandler( leh, ltp );
			this->reactor->RegisterHandler( lfeh, READ_EVENT );
		}
		//reactivate the handle.
//		ltp->ReactivateHandle( handle, et );

	}

	virtual HANDLE GetHandle(void)
	{
		return acceptor.GetHandle();
	}
private:
	// Socket factory that accepts client connections
	SockAcceptor acceptor;
	
	// Cached <Reactor>.
	Reactor *reactor;
	bool isActive;
	LFThreadPool* ltp;
};
