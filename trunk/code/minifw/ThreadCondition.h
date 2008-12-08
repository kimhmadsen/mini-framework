#pragma once
#include "threadmutex.h"

/**
Implements the wrapper facade for Condition variable defined in POSA2 page 59

*/
class ThreadCondition
{
public:

	ThreadCondition(const ThreadMutex &m) : mutex(m)
	{
		cond = InitializeCondition(
	}

	~ThreadCondition(void)
	{

	}

	void Wait(TIMEVAL *timeout = 0)
	{
	
	}

	void Notify()
	{

	}

	void NotifyAll()
	{

	}

private:
	HANDLE cond; 
	const ThreadMutex &mutex;
};
