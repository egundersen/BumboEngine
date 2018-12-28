#include "EventBase.h"

#ifndef EVENT_BRIDGERALLY_H
#define EVENT_BRIDGERALLY_H

class Event_BridgeRally : public EventBase
{
public:
	using EventBase::EventBase;

	void createEvent();
	void refreshEvent();
};

#endif // !EVENT_BRIDGERALLY_H