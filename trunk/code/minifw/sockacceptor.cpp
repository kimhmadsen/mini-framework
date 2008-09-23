#include "StdAfx.h"
#include "sockacceptor.h"

SockAcceptor::SockAcceptor( InetAddr &sock_addr )
{

	SockAcceptor::open( sock_addr );
}

SockAcceptor::~SockAcceptor(void)
{

}

// A second method to initialize a  passive-mode
// acceptor socket, analogously to the contructor
void SockAcceptor::open( InetAddr &sock_addr )
{
	// create a local endpoint of communication
	handle = (HANDLE)socket( PF_INET, SOCK_STREAM, 0 );
	// Associate address with endpoint
	bind( (SOCKET)handle, sock_addr.Addr(), sock_addr.Size() );
	// Make endpoint listen for connections.
	listen( (SOCKET)handle, 5 );
}

void SockAcceptor::accept( SockStream &s)
{
	s.SetHandle( (HANDLE)::accept( (SOCKET)handle, 0, 0 ) );
}

HANDLE SockAcceptor::GetHandle() const
{
	return handle;
}
