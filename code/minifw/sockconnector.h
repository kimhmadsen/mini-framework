#pragma once

#include "sockstream.h"
#include "inetaddr.h"

class SOCK_Connector
{
public:
	SOCK_Connector(void);
	~SOCK_Connector(void);
	void connect( SockStream &stream, InetAddr addr );
};
