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
	void approachCheckpoint(int position_x, int position_y);
	void runsThroughCheckpoint(int position_x, int position_y);
	void guardStopThem();
	void guardExits();
	void playerThinks();

	void crowdLook1();
	void crowdLook2();
	void resetMovementIndexes();
};

#endif // !EVENT_BORDERINCIDENT_H
