#include "StdAfx.h"
#include "SOCK_Stream.h"

//SOCK_Stream::SOCK_Stream(void)
//{
//	//handle_ = INVALID_HANDLE_VALUE;	
//	handle_ = socket(PF_INET, SOCK_STREAM, 0); // do some error checking!
//}

SOCK_Stream::~SOCK_Stream(void)
{
	closesocket( (SOCKET)handle_);
}

void SOCK_Stream::set_handle( HANDLE h )
{
	handle_ = h;
}

HANDLE SOCK_Stream::get_handle(void)
{
	return (HANDLE)handle_;
}

ssize_t SOCK_Stream::recv ( void* buf, size_t len, int flags )
{
	return ::recv( (SOCKET)handle_, (char*)buf, len, flags );
}

ssize_t SOCK_Stream::send ( const char* buf, size_t len,  int flags )
{
	return ::send((SOCKET)handle_, buf, len, flags );
}

ssize_t SOCK_Stream::recv_n (void* buf, size_t len, int flags )
{
	ssize_t n = 0;

	for( size_t nread=0; nread < len; nread += n )
	{
		n = ::recv( (SOCKET)handle_, (char*)buf + nread, len - nread, flags );
		if( n <= 0 ) return 0;
	}
	return len; 
}

ssize_t SOCK_Stream::send_n (const char* buf, size_t len,  int flags )
{
	ssize_t n = 0;

	for( size_t nsent = 0; nsent < len; nsent += n )
	{
		n = ::send( (SOCKET)handle_, buf, len, flags );
		if( n <= 0 ) return 0;
	}
	return len;
}

void SOCK_Stream::close(void)
{
	::closesocket( (SOCKET)handle_ );
}
