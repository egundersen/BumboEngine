#ifndef EVENT_TEST_H
#define EVENT_TEST_H

#include "EventBase.h"

// For testing only, displays a simple popup
class Event_Test : public EventBase
{
public:
	using EventBase::EventBase;

	void createEvent();
	void refreshEvent();
};

#endif // !EVENT_TEST_H