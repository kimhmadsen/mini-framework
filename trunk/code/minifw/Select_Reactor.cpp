#include "StdAfx.h"
#include "Select_Reactor.h"
#include "Reactor_Implementation.h"

Select_Reactor* Select_Reactor::instance_ = 0;

Select_Reactor::Select_Reactor(void)
{
	reactor_impl_ = new Select_Reactor_Implementation();
}

Select_Reactor::~Select_Reactor(void)
{
	reactor_impl_->~Reactor_Implementation();
	delete reactor_impl_;
}


Reactor* Select_Reactor::instance(void)
{
	if( instance_ == 0 )
	{
		instance_ = new Select_Reactor();
	}
	return instance_;
}


void Select_Reactor::register_handler(Event_Handler *eh, Event_Type et)
{
	reactor_impl_->register_handler( eh, et );
}

void Select_Reactor::register_handler(HANDLE h, Event_Handler *eh, Event_Type et)
{
	reactor_impl_->register_handler( h, eh, et );
}

void Select_Reactor::remove_handler(Event_Handler *eh, Event_Type et)
{
	reactor_impl_->remove_handler( eh, et );
}

void Select_Reactor::remove_handler(HANDLE h, Event_Type et) const
{
	reactor_impl_->remove_handler( h, et );
}


