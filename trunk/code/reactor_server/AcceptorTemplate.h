#pragma once

#include "eventhandler.h"
#include "sockacceptor.h"
#include "reactor.h"

template <class EVENT_HANDLER> class AcceptorTemplate :
	public EventHandler
{
public:
	AcceptorTemplate( InetAddr &addr, Reactor *reactor );
	~AcceptorTemplate(void);
	virtual void HandleEvent(HANDLE handle, Event_Type et );
	virtual HANDLE GetHandle(void);
private:
	// Socket factory that accepts client connections
	SockAcceptor acceptor;
	// Cached <Reactor>.
	Reactor *reactor;

};
