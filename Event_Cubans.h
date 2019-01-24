#ifndef EVENT_CUBANS_H
#define EVENT_CUBANS_H

#include "EventBase.h"

// Cubans show up and make an NPC dissapear
class Event_Cubans : public EventBase
{
public:
	using EventBase::EventBase;

	void createEvent();
	void refreshEvent();
private:
	void moveCubans();
	void speak();
	void leave();
};

#endif // !EVENT_CUBANS_H