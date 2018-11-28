#include "EventBase.h"

#ifndef EVENT_BORDERINCIDENT_H
#define EVENT_BORDERINCIDENT_H

class Event_BorderIncident : public EventBase
{
public:
	using EventBase::EventBase;

	void createEvent();
	void refreshEvent();
private:
	// Parts of the event
	void guardTalks();
	void crowdLooksAround();
	void guardReplies();
	void runsThroughCheckpoint();
	void guardStopThem();
	void guardExits();
	void playerDroppedSomething();

	void crowdLook1();
	void crowdLook2();
};

#endif // !EVENT_BORDERINCIDENT_H
