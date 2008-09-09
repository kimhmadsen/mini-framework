#pragma once
#include "event_handler.h"

class LogEventHandler :
	public Event_Handler
{
public:
	LogEventHandler(void);
	~LogEventHandler(void);
};
