#ifndef EVENT_THROWOFFCLIFF_H
#define EVENT_THROWOFFCLIFF_H

#include "EventBase.h"

class Event_ThrowOffCliff : public EventBase
{
public:
	using EventBase::EventBase;

	void createEvent();
	void refreshEvent();
private:
	void speak1();
	void move();
	void speak2();
	void throwOffCliff();

	int go_down_iterator_, fall_speed_;
};

#endif // !EVENT_THROWOFFCLIFF_H