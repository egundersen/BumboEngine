#include "EventBase.h"

#ifndef EVENT_TEST_H
#define EVENT_TEST_H

class Event_Test : public EventBase
{
public:
	using EventBase::EventBase;

	void createEvent();
	void refreshEvent();
};

#endif // !EVENT_TEST_H