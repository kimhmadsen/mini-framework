#pragma once
#include "reactor.h"
#include "threadmutex.h"
#include "guard.h"
#include "thread.h"
#define NO_CURRENT_LEADER 0 

/**
Implements the Thrad Pool class defiens by POSA2 page 453

Responsibility:
- Threads that take turns playing three roles: in the leader role they await 
events, in the process events, in the follower role they queue up waiting to 
become the leader.

Collaborator:
- HandleSet
- Handle
- EventHandler
*/
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
