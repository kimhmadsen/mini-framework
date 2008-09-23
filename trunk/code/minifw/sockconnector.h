#pragma once

#include "sockstream.h"
#include "inetaddr.h"

class SOCK_Connector
{
public:
	SOCK_Connector(void);
	~SOCK_Connector(void);
	void connect( SOCK_Stream &stream, INET_Addr addr );
};
