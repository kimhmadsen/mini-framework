#pragma once

typedef int SOCKET;
const int INVALID_HANDLE_VALUE = -1;

#include <sockLib.h> 

class SOCK_Stream
{
public:
	SOCK_Stream(void): handle_(INVALID_HANDLE_VALUE){}
	SOCK_Stream(int h): handle_( h ){}
	~SOCK_Stream(void);
	void    set_handle( int h );
	int  get_handle(void);
	ssize_t recv (void* buf, size_t len, int flags);
	ssize_t send (const char* buf, size_t len,  int flags);

	// 
	ssize_t recv_n (void* buf, size_t len, int flags);
	ssize_t send_n (const char* buf, size_t len,  int flags);

	void close(void);
private:
	int handle_;
	//SOCKET handle_;
};
