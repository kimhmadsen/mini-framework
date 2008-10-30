#pragma once
class ThreadMutex
{
public:

	ThreadMutex(void)
	{
		mutex = CreateMutex(NULL,false,NULL);
	}

	~ThreadMutex(void)
	{
		CloseHandle(mutex);
	}

	void Aquire()
	{
		WaitForSingleObject(mutex,INFINITE);
	}

	void Release()
	{
		ReleaseMutex(mutex);
	}

private:
	HANDLE mutex;
	ThreadMutex(const ThreadMutex&);
	void operator=(const ThreadMutex&);
	friend class ThreadCondition;

};
