#include "StdAfx.h"
#include "LFEventHandler.h"

LFEventHandler::LFEventHandler(EventHandler *eh, LFThreadPool *tp)
: theHandler(eh), ltp(tp)
{
	SetHandle( eh->GetHandle() );
}

LFEventHandler::~LFEventHandler(void)
{
	delete this->theHandler;
}

void LFEventHandler::HandleEvent(HANDLE h, Event_Type et)
{
	
	//deactivate the handle.
	ltp->DeactivateHandle( h, et );

	ltp->PromoteNewLeader();

	theHandler->HandleEvent(h, et );
	
	//reactivate the handle.
	ltp->ReactivateHandle( h, et );

}