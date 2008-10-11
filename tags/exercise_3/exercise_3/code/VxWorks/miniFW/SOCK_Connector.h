#pragma once

#include "SOCK_Stream.h"
#include "INET_Addr.h"
#include <stdio.h>

class SOCK_Connector
{
public:
	SOCK_Connector(void);
	~SOCK_Connector(void);
	void connect( SOCK_Stream &stream, INET_Addr addr );
};
