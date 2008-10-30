#pragma once

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
