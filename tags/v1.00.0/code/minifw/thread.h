#pragma once
#ifdef WIN32
typedef DWORD thread_t;
#endif

/**
Implements wrapper facade class the the Thread provided by the OS

*/
class Thread
{
public:
	Thread(void);
	~Thread(void);
	static thread_t Self(void);
};
