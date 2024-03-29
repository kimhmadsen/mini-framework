#pragma once
#include <unistd.h>
#include <sys/socket.h>

typedef int HANDLE;

class SynchEventDemux
{
public:
	SynchEventDemux(void);
	~SynchEventDemux(void);
	int select(unsigned int width, fd_set *read_fds, fd_set *write_fds, fd_set *except_fds, timeval *timeout);
};
