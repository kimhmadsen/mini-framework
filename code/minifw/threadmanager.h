#pragma once
#include "thread.h"

// GoF Wrapper class for the thread API provided by the OS.
class ThreadManager
{
public:
	// GoF singleton patterns 
	static ThreadManager *Instance();
	// Spawn a thread 
	void Spawn( void* (*entryPointFunction) (void *), void *arg = 0, 
														long flags = 0, 
														long stackSize = 0, 
														void *stackPointer = 0, 
														thread_t *threadId = 0 );

private:
	ThreadManager(void);
	~ThreadManager(void);

	static ThreadManager *instance;
};
