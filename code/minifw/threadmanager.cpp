#include "StdAfx.h"
#include "threadmanager.h"
#include <windows.h>
#include <strsafe.h>


ThreadManager::ThreadManager(void)
{
}

ThreadManager::~ThreadManager(void)
{
}

ThreadManager* ThreadManager::Instance(void)
{
	if( instance == 0 )
	{
		instance = new ThreadManager();
	}
	return instance;
}

void ThreadManager::Spawn( void* (*entryPointFunction) (void *), void *arg, 
														           long flags, 
														           long stackSize, 
														           void *stackPointer, 
														           thread_t *threadId )
{
	CreateThread( NULL, stackSize, (LPTHREAD_START_ROUTINE)entryPointFunction, arg, flags, threadId ); 
}
