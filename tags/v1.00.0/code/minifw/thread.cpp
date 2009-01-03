#include "StdAfx.h"
#include "thread.h"

Thread::Thread(void)
{
}

Thread::~Thread(void)
{
}

thread_t Thread::Self(void)
{
	return GetCurrentThreadId();
}