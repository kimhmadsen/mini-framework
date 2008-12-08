#pragma once

/**
Implements the interface defined in POSA2 page 336

*/
class Lock
{
public:
	virtual void Acquire()=0;
	virtual void Release()=0;

private:

	Lock(void)
	{
	}

	~Lock(void)
	{
	}
};
