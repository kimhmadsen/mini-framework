
#include "StdAfx.h"
#include "eventhandler.h"

EventHandler::EventHandler(void)
{
}

EventHandler::~EventHandler(void)
{
}

HANDLE EventHandler::GetHandle(void)
{
	return handle;
}

void EventHandler::SetHandle(HANDLE handle)
{
	this->handle = handle;
}