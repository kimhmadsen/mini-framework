#pragma once
#include "event_handler.h"

class PatientValueEventHandler :
	public Event_Handler
{
public:
	PatientValueEventHandler(void);
	~PatientValueEventHandler(void);
};
