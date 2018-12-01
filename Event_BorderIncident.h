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
	void guardTalks(int time_interval);
	void crowdLooksAround();
	void guardReplies(int time_interval);
	void runsThroughCheckpoint();
	void guardStopThem(int time_interval);
	void guardExits();
	void playerDroppedSomething(int time_interval);

	void crowdLook1();
	void crowdLook2();
};

#endif // !EVENT_BORDERINCIDENT_H
