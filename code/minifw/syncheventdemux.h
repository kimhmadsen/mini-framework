#pragma once

class SynchEventDemux
{
public:
	SynchEventDemux(void);
	~SynchEventDemux(void);
	int SEDselect(unsigned int width, fd_set *read_fds, fd_set *write_fds, fd_set *except_fds, timeval *timeout);
};
