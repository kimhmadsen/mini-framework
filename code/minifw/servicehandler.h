#pragma once
#include "eventhandler.h"
#include "sockstream.h"

/**
Service handler
Responsibility:
- Implementats a half of an end-to-end servie in a networked application.

Collaborator
- Dispatcher eg. Reactor
- Transport Endpoint
*/
template <class IPC_STREAM>
class ServiceHandler : public EventHandler
{
public:
	typedef typename IPC_STREAM::PEER_ADDR Addr;
//	ServiceHandler(void);
//	~ServiceHandler(void);
	// Pure virtual method (deifned by a subclass)
	virtual void open() = 0;

	// Access method used by <Acceptor> and <Connector>.
	IPC_STREAM &Peer() { return ipc_stream; }

	// Return the address we are connected to.
	Addr &RemoteAddr() { return ipc_stream.RemoteAddr() }

	//Set the <handle> used by this <ServiceHandler>
	void SetHandle( HANDLE handle ) { return ipc_stream.SetHandle( handle ) }

private:
	// Template 'placeholder' for a concrete IPC 
	// mechanism wrapper facade, which emcapsulates a 
	// data-mode transport.
	IPC_STREAM ipc_stream;

};
