#include "StdAfx.h"
#include "sockstream.h"

SockStream::SockStream(void): handle(INVALID_HANDLE_VALUE)
{
}

SockStream::SockStream(HANDLE h): handle( h )
{
}

SockStream::SockStream(const SockStream& ss )
{
	this->handle = ss.handle;
}


SockStream::~SockStream(void)
{
	closesocket( (SOCKET)handle);
}

void SockStream::SetHandle( HANDLE h )
{
	handle = h;
}

HANDLE SockStream::GetHandle(void)
{
	return (HANDLE)handle;
}

ssize_t SockStream::recv ( void* buf, size_t len, int flags )
{
	return ::recv( (SOCKET)handle, (char*)buf, len, flags );
}

ssize_t SockStream::send ( const char* buf, size_t len,  int flags )
{
	return ::send((SOCKET)handle, buf, len, flags );
}

ssize_t SockStream::recv_n (void* buf, size_t len, int flags )
{
	ssize_t n = 0;

	for( size_t nread=0; nread < len; nread += n )
	{
		n = ::recv( (SOCKET)handle, (char*)buf + nread, len - nread, flags );
		if( n <= 0 ) return 0;
	}
	return len; 
}

ssize_t SockStream::send_n (const char* buf, size_t len,  int flags )
{
	ssize_t n = 0;

	for( size_t nsent = 0; nsent < len; nsent += n )
	{
		n = ::send( (SOCKET)handle, buf, len, flags );
		if( n <= 0 ) return 0;
	}
	return len;
}

void SockStream::close(void)
{
	::closesocket( (SOCKET)handle );
}
