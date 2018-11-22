#include "EventBase.h"

#ifndef EVENT_ATTACKONSIGHT_H
#define EVENT_ATTACKONSIGHT_H

class Event_AttackOnSight : public EventBase
{
public:
	using EventBase::EventBase;

	void createEvent();
	void refreshEvent();
};

#endif // !EVENT_ATTACKONSIGHT_H
