#include "StdAfx.h"
#include "LFEventHandler.h"

LFEventHandler::LFEventHandler(EventHandler *eh, LFThreadPool *tp)
: theHandler(eh), ltp(tp)
{

}

LFEventHandler::~LFEventHandler(void)
{
}

void LFEventHandler::HandleEvent(HANDLE h, Event_Type et)
{
	//deactivate the handle.
	ltp->PromoteNewLeader();
	//reactivate the handle.
}