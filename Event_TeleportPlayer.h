#include "EventBase.h"

#ifndef EVENT_TELEPORTPLAYER_H
#define EVENT_TELEPORTPLAYER_H

class Event_TeleportPlayer : public EventBase
{
public:
	using EventBase::EventBase;

	void createEvent();
	void refreshEvent();
};

#endif // !EVENT_TELEPORTPLAYER_H
