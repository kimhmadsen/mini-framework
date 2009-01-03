#pragma once
/**
@file
*/
#include "threadmutex.h"

/**
Implements The Scoped Locking C++ idiom which ensures that a lock is acquired 
when control enters a scope and released automatically when control leaves the 
scope, regardless of the return path from the scope.

*/
class Guard
{
public:

	Guard(ThreadMutex &lock_)
		:lock(&lock_), owner(false)
	{
		lock->Acquire();
		owner = true	;
	}

	~Guard(void)
	{
		if(owner)
			lock->Release();
	}

	void Acquire()
	{
		lock->Acquire();
		owner = true;

	}

	void Release()
	{
		lock->Release();
		owner = false;
	}

private:
	ThreadMutex *lock;
	bool owner;
	Guard(const Guard &);
	void operator=(const Guard &);
};
