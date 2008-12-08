#pragma once

/**
Implements the synchronous event demultiplexer defines by POSA2 on page 183

Responsibility:
- Can block waiting for indication events to occur on a handle set
- Indicates an operation can be initiated on a handle without blocking

Collaborator:
- Handle
- HandleSet
*/
class SynchEventDemux
{
public:
	SynchEventDemux(void);
	~SynchEventDemux(void);
	int select(unsigned int width, fd_set *read_fds, fd_set *write_fds, fd_set *except_fds, timeval *timeout);
};
