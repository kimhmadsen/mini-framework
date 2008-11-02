#pragma once
#include "reactor.h"
#include "threadmutex.h"
#include "guard.h"
#include "thread.h"
#define NO_CURRENT_LEADER 0 

class LFThreadPool
{
public:
	LFThreadPool(Reactor *r);
	void JoinPool(TIMEVAL *timeout=0);
	void PromoteNewLeader();
	void DeactivateHandle(HANDLE h, Event_Type et);
	void ReactivateHandle(HANDLE h, Event_Type et);
	~LFThreadPool(void);

private:
	Reactor *reactor;
	int leaderThread;
	ThreadMutex followersCondition;
	ThreadMutex mutex;

};
