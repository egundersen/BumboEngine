#include "EventBase.h"
#ifndef EVENT_TEST
#define EVENT_TEST

class Event_Test : public EventBase
{
public:
	using EventBase::EventBase;

	void refreshEvent();
};

#endif // !EVENT_TEST
