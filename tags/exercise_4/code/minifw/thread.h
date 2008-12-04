#pragma once
#ifdef WIN32
typedef DWORD thread_t;
#endif

class Thread
{
public:
	Thread(void);
	~Thread(void);
	static thread_t Self(void);
};
