#include "EventBase.h"

#ifndef EVENT_BRIDGERALLY2_H
#define EVENT_BRIDGERALLY2_H

class Event_BridgeRally2 : public EventBase
{
public:
	using EventBase::EventBase;

	void createEvent();
	void refreshEvent();
};

#endif // !EVENT_BRIDGERALLY2_H