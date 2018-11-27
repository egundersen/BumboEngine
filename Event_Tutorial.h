#include "EventBase.h"

#ifndef EVENT_TUTORIAL_H
#define EVENT_TUTORIAL_H

class Event_Tutorial : public EventBase
{
public:
	Event_Tutorial(int unique_object_ID, int center_position_x, int center_position_y, int collider_width, int collider_height, int character_ID,
		std::vector<std::vector<std::pair<int, int>>> &element_has_object, std::vector<std::vector<std::string>> &matrix_display, std::vector<CharacterBase*> &characters, ScreenPosition &screen_position, int screen_width, int screen_height);

	void createEvent();
	void refreshEvent();

private:
	// Parts of the event (In-Order)
	void moveTutorialNpc();
	void askPlayerName(int time_interval);
	void getPlayerName();
	void tellFatherBackstory(int time_interval);
	void skipTutorial();
	void tutorial();

	// Functions used by the event
	void displayDialogChoice(int position_x, int position_y);
	void confirmSelection();

	int dialog_choice_index_, go_down_iterator_, fall_speed;
	bool should_go_down_, has_entered_name_;
};

#endif // !EVENT_TUTORIAL_H
