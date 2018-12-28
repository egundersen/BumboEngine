#include "EventBase.h"

#ifndef EVENT_CUBANS_H
#define EVENT_CUBANS_H

class Event_Cubans : public EventBase
{
public:
	using EventBase::EventBase;

	void createEvent();
	void refreshEvent();
};

#endif // !EVENT_CUBANS_H