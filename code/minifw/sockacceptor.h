#pragma once

#include "inetaddr.h"
#include "sockstream.h"

/**
Acceptor for socket connections.
Responsibility:
- Passivily connects and initializes an associated Service Handler

Collaborator:
- Service Handler
- Dispaatcher
- Transport Endpoint
 */
class SockAcceptor
{
public:
	SockAcceptor( InetAddr &sock_addr );
	~SockAcceptor(void);

	void open( InetAddr &sock_addr );
	void accept( SockStream &s);
	HANDLE GetHandle() const;
private:
	HANDLE handle;
};
