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
		while(leaderThread != NO_CURRENT_LEADER && leaderThread != Thread::Self() )
		{
			// NOT thread safe should have been made with a Conditionvariable. But windows does not support 
			// condition variables. 
			mutex.Release();
			followersCondition.Acquire(150);
			mutex.Acquire();
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
	if(leaderThread != Thread::Self() )
		std::cout << "PromoteNewLeader"<< std::endl;

	leaderThread = NO_CURRENT_LEADER;
	followersCondition.Release();
}

void LFThreadPool::DeactivateHandle(HANDLE h, Event_Type et)
{
	//reactor = Reactor::instance();
	reactor->DeactivateHandle(h, et );
}

void LFThreadPool::ReactivateHandle(HANDLE h, Event_Type et)
{
	reactor->ReactivateHandle( h, et );
}

