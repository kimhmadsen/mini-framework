#pragma once
#include "LFEventHandler.h"
#include "LFThreadPool.h"
#include "inetaddr.h"
#include "sockacceptor.h"
#include "reactor.h"

class ClientAcceptor :
	public LFEventHandler
{
public:
	ClientAcceptor(InetAddr &addr, Reactor *reactor, LFThreadPool *tp );
	~ClientAcceptor(void);
	void HandleEvent(HANDLE h, Event_Type et);
private:
	// Socket factory that accepts client connections
	SockAcceptor acceptor;
	// Cached <Reactor>.
	Reactor *reactor;
	bool isActive;


};
