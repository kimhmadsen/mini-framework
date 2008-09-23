#pragma once

#include "inetaddr.h"
#include "sockstream.h"

class SOCK_Acceptor
{
public:
	SOCK_Acceptor( INET_Addr &sock_addr );
	~SOCK_Acceptor(void);

	void open( INET_Addr &sock_addr );
	void accept( SOCK_Stream &s);
	HANDLE get_handle() const;
private:
	HANDLE handle_;
};
