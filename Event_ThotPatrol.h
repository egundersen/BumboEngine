#include "EventBase.h"

#ifndef EVENT_THOTPATROL_H
#define EVENT_THOTPATROL_H

class Event_ThotPatrol : public EventBase
{
public:
	using EventBase::EventBase;

	void createEvent();
	void refreshEvent();
private:
	void moveToPlayer();
	void speak();
	void battle();
};

#endif // !EVENT_THOTPATROL_H