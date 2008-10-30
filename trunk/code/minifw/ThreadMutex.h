#pragma once
class ThreadMutex
{
public:

	ThreadMutex(void)
	{
		mutex = CreateMutex(NULL,false,NULL);
		//InitializeCriticalSection(&mutex);
	}

	~ThreadMutex(void)
	{
		CloseHandle(mutex);
		//DeleteCriticalSection(&mutex);
	}

	void Acquire(int ms = INFINITE)
	{
		WaitForSingleObject(mutex, ms);
		//EnterCriticalSection(&mutex);
	}

	void Release()
	{
		ReleaseMutex(mutex);
		//LeaveCriticalSection(&mutex);
	}

private:
	HANDLE mutex;
	//CRITICAL_SECTION mutex;
	ThreadMutex(const ThreadMutex&);
	void operator=(const ThreadMutex&);
	//friend class ThreadCondition;

};
