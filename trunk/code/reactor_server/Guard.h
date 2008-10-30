#pragma once
#include "threadmutex.h"

class Guard
{
public:

	Guard(ThreadMutex &lock_)
		:lock(lock), owner(false)
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
