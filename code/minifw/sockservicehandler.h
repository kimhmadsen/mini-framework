#pragma once
#include "eventhandler.h"
#include "sockstream.h"

class SockServiceHandler :
	public EventHandler
{
public:
	SockServiceHandler(void);
	~SockServiceHandler(void);
	virtual void open() = 0;
	SockStream &peer();

};
