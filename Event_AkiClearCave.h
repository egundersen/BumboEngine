#include "EventBase.h"

#ifndef EVENT_AKICLEARCAVE_H
#define EVENT_AKICLEARCAVE_H

class Event_AkiClearCave : public EventBase
{
public:
	using EventBase::EventBase;

	void createEvent();
	void refreshEvent();
	bool isAvailable();
private:
	void lookAround();
	void moveToPlayer();
	void speak();
	void leave();
};

#endif // !EVENT_AKICLEARCAVE_H