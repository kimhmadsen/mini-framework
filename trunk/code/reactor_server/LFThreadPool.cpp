#include "LFThreadPool.h"

LFThreadPool::LFThreadPool(Reactor *r)
: reactor(r)
{ 
	leaderThread = NO_CURRENT_LEADER;
}

LFThreadPool::~LFThreadPool(void)
{
}

void LFThreadPool::JoinPool(TIMEVAL *timeout)
{
	for(;;)
	{
		while(leaderThread != NO_CURRENT_LEADER)
			Sleep(15);

		leaderThread = 1;
	}
}

void LFThreadPool::PromoteNewLeader()
{

}

void LFThreadPool::DeactivateHandle(HANDLE h, Event_Type et)
{

}

void LFThreadPool::ReactivateHandle(HANDLE h, Event_Type et)
{

}

