#include "EventBase.h"

#ifndef EVENT_TUTORIAL_H
#define EVENT_TUTORIAL_H

class Event_Tutorial : public EventBase
{
public:
	using EventBase::EventBase;

	void createEvent();
	void refreshEvent();

private:
	// Parts of the event
	void moveManny(int time_interval);
	void beforeTutorial(int time_interval);
	void tutorial();
	void getPlayerName();
	void skipTutorial();

	// Functions used by the event
	void displayDialogChoice(int position_x, int position_y);
	void confirmSelection();

	int event_index_ = 0, dialog_choice_index_ = 0, go_down_iterator_ = 0, fall_speed = 125;
	bool should_go_down_ = false, has_entered_name_ = false;
};

#endif // !EVENT_TUTORIAL_H
