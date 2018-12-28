#include "EventBase.h"

#ifndef EVENT_BRIDGERALLY3_H
#define EVENT_BRIDGERALLY3_H

class Event_BridgeRally3 : public EventBase
{
public:
	using EventBase::EventBase;

	void createEvent();
	void refreshEvent();
};

#endif // !EVENT_BRIDGERALLY3_H