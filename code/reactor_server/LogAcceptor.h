#pragma once
#include "eventhandler.h"
#include "reactor.h"
#include "sockacceptor.h"
#include "logeventhandler.h"

class LogAcceptor :
	public EventHandler
{
public:
	LogAcceptor( InetAddr &addr, Reactor *reactor );
	~LogAcceptor(void);

	virtual void HandleEvent(HANDLE handle, Event_Type et );
	virtual HANDLE GetHandle(void);
private:
	// Socket factory that accepts client connections
	SockAcceptor acceptor;
	// Cached <Reactor>.
	Reactor *reactor;
};
