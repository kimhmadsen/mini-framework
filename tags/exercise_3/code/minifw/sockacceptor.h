#pragma once

#include "inetaddr.h"
#include "sockstream.h"

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
