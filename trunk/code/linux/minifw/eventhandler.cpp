
#include "stdafx.h"
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
