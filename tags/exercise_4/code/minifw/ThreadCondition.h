#pragma once
#include "threadmutex.h"

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
