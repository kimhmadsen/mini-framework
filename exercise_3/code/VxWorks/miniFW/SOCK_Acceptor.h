#pragma once

#include "INET_Addr.h"
#include "SOCK_Stream.h"

class SOCK_Acceptor
{
public:
	SOCK_Acceptor( INET_Addr &sock_addr );
	~SOCK_Acceptor(void);

	void open( INET_Addr &sock_addr );
	void accept( SOCK_Stream &s);
	int get_handle() const;
private:
	int handle_;
};
