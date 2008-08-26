#pragma once

#include "SOCK_Stream.h"
#include "INET_Addr.h"

class SOCK_Connector
{
public:
	SOCK_Connector(void);
	~SOCK_Connector(void);
	connect( SOCK_Stream stream, INET_Addr addr );
};
