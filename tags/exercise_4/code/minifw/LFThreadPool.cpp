#include "StdAfx.h"
#include "lfthreadpool.h"
#include <iostream>

LFThreadPool::LFThreadPool(Reactor *r)
: reactor(r)
{ 
	leaderThread = NO_CURRENT_LEADER;
//	followersCondition
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
			mutex.Acquire(150);
		}

		leaderThread = Thread::Self();
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

	mutex.Release();
}

void LFThreadPool::DeactivateHandle(HANDLE h, Event_Type et)
{
	
}

void LFThreadPool::ReactivateHandle(HANDLE h, Event_Type et)
{

}

