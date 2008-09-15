#include "StdAfx.h"
#include "Reactor.h"

static Reactor* Reactor::instance_ = 0;

Reactor::Reactor(void)
{
	reactor_impl_ = new Reactor_Implementation();
}

Reactor::~Reactor(void)
{
	delete reactor_impl_;
}
