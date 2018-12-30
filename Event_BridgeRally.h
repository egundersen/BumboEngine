#include "EventBase.h"

#ifndef EVENT_BRIDGERALLY_H
#define EVENT_BRIDGERALLY_H

class Event_BridgeRally : public EventBase
{
public:
	using EventBase::EventBase;

	void createEvent();
	void refreshEvent();
private:
	void speak();
	void leave();
};

#endif // !EVENT_BRIDGERALLY_H