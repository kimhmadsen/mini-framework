#include "LFThreadPool.h"
#include <iostream>

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
	Guard guard(mutex);
	for(;;)
	{
		while(leaderThread != NO_CURRENT_LEADER)
		{
			//followersCondition.Release();
			followersCondition.Acquire(15);
		}

		leaderThread = 1;
		guard.Release();
		reactor->HandleEvents();
		guard.Acquire();			
	}
}

void LFThreadPool::PromoteNewLeader()
{
	Guard guard(mutex);
	if(leaderThread != 1)
		std::cout << "CRAP"<< std::endl;

	leaderThread = NO_CURRENT_LEADER;

	followersCondition.Release();  //perhaps not needed
}

void LFThreadPool::DeactivateHandle(HANDLE h, Event_Type et)
{

}

void LFThreadPool::ReactivateHandle(HANDLE h, Event_Type et)
{

}

