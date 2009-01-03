#pragma once

#include "sockstream.h"
#include "inetaddr.h"

/**
Connector for socket connections.
Responsibility:
- Actively connects andinitializes an associated Service Handler

Collaborator:
- Service Handler
- Dispatcher
- Transport Endpoint
 */
class SOCK_Connector
{
public:
	SOCK_Connector(void);
	~SOCK_Connector(void);
	int connect( SockStream &stream, InetAddr addr );
	void close(SockStream &stream);
};
