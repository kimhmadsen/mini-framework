#include "StdAfx.h"
#include "SOCK_Acceptor.h"

SOCK_Acceptor::SOCK_Acceptor( INET_Addr &sock_addr )
{
	// create a local endpoint of communication
	handle_ = socket( PF_INET, SOCK_STREAM, 0 );
	// Associate address with endpoint
	bind( handle_, sock_addr.addr(), sock_addr.size() );
	// Make endpoint listen for connections.
	listen( handle_, 5 );
}

SOCK_Acceptor::~SOCK_Acceptor(void)
{

}

// A second method to initialize a  passive-mode
// acceptor socket, analogously to the contructor
void SOCK_Acceptor::open( INET_Addr &sock_addr )
{
	// create a local endpoint of communication
	handle_ = socket( PF_INET, SOCK_STREAM, 0 );
	// Associate address with endpoint
	bind( handle_, sock_addr.addr(), sock_addr.size() );
	// Make endpoint listen for connections.
	listen( handle_, 5 );
}

void SOCK_Acceptor::accept( SOCK_Stream &s)
{
	s.set_handle( ::accept( handle_, 0, 0 ) );
}
