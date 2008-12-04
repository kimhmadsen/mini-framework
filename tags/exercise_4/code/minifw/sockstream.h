#pragma once
#ifdef WIN32
#include <windows.h>
#include <winsock.h>
typedef int ssize_t;
//const int INVALID_HANDLE_VALUE = -1;
#elif
typedef int SOCKET;
const int INVALID_HANDLE_VALUE = -1;
#endif

/**
Implement a Wrapper Facade for the socket data structure.
Responsibility:
- Encapsulates socket structures with a cohesive objectoriented abstraction.

Collaborator:
- HANDLE

*/
class SockStream
{
public:
	SockStream(void);
	SockStream(HANDLE h);
	SockStream(const SockStream& ss );
	~SockStream(void);
	void    SetHandle( HANDLE h );
	HANDLE  GetHandle(void);
	ssize_t recv (void* buf, size_t len, int flags);
	ssize_t send (const char* buf, size_t len,  int flags);

	// 
	ssize_t recv_n (void* buf, size_t len, int flags);
	ssize_t send_n (const char* buf, size_t len,  int flags);

	void close(void);
private:
	HANDLE handle;
	//SOCKET handle;
};
