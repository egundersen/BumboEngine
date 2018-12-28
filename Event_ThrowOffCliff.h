#include "EventBase.h"

#ifndef EVENT_THROWOFFCLIFF_H
#define EVENT_THROWOFFCLIFF_H

class Event_ThrowOffCliff : public EventBase
{
public:
	using EventBase::EventBase;

	void createEvent();
	void refreshEvent();
};

#endif // !EVENT_THROWOFFCLIFF_H