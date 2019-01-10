#ifndef EVENT_TEST_H
#define EVENT_TEST_H

#include "EventBase.h"

class Event_Test : public EventBase
{
public:
	using EventBase::EventBase;

	void createEvent();
	void refreshEvent();
};

#endif // !EVENT_TEST_H