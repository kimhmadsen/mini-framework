#pragma once
#ifdef WIN32
#include <windows.h>
#include <winsock.h>
typedef int ssize_t;
#elif
typedef int SOCKET;
const int INVALID_HANDLE_VALUE = -1;
#endif


class SOCK_Stream
{
public:
	SOCK_Stream(void): handle_(INVALID_SOCKET){}
	SOCK_Stream(SOCKET h): handle_( h ){}
	~SOCK_Stream(void);
	void    set_handle( SOCKET h );
	SOCKET  get_handle(void);
	ssize_t recv (void* buf, size_t len, int flags);
	ssize_t send (const char* buf, size_t len,  int flags);

	// 
	ssize_t recv_n (void* buf, size_t len, int flags);
	ssize_t send_n (const char* buf, size_t len,  int flags);

	void close(void);
private:
	SOCKET handle_;
};
