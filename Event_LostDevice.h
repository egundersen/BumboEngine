#include "EventBase.h"

#ifndef EVENT_LOSTDEVICE_H
#define EVENT_LOSTDEVICE_H

class Event_LostDevice : public EventBase
{
public:
	using EventBase::EventBase;

	void createEvent();
	void refreshEvent();
};

#endif // !EVENT_LOSTDEVICE_H