#include "stdafx.h"
#include "syncheventdemux.h"

SynchEventDemux::SynchEventDemux(void)
{
}

SynchEventDemux::~SynchEventDemux(void)
{
}

int SynchEventDemux::select(unsigned int width, fd_set *read_fds, fd_set *write_fds, fd_set *except_fds, timeval *timeout) 
{
	return (int)(HANDLE)::select(width, read_fds, write_fds, except_fds, timeout);
}
