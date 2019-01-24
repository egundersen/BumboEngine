#ifndef EVENT_BRIDGERALLY2_H
#define EVENT_BRIDGERALLY2_H

#include "EventBase.h"

// Pirates see someone on the bridge, but decide to cross anyway
class Event_BridgeRally2 : public EventBase
{
public:
	using EventBase::EventBase;

	void createEvent();
	void refreshEvent();
private:
	void speak();
	void leave();
};

#endif // !EVENT_BRIDGERALLY2_H