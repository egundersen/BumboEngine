#include "EventBase.h"

#ifndef EVENT_BORDERINCIDENT_H
#define EVENT_BORDERINCIDENT_H

class Event_BorderIncident : public EventBase
{
public:
	using EventBase::EventBase;

	void createEvent();
	void refreshEvent();
};

#endif // !EVENT_BORDERINCIDENT_H
