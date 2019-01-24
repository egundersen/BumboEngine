#ifndef EVENT_ROLLCREDITS_H
#define EVENT_ROLLCREDITS_H

#include "EventBase.h"

// Changes to the credits scene
class Event_RollCredits : public EventBase
{
public:
	Event_RollCredits(int unique_object_ID, bool &should_roll_credits,
		std::vector<std::vector<std::pair<int, int>>> &element_has_object, Matrix &screen_matrix, std::vector<CharacterBase*> &characters, ScreenPosition &screen_position, int screen_width, int screen_height);

	void createEvent();
	void refreshEvent();
private:
	bool &should_roll_credits_;
};

#endif // !EVENT_ROLLCREDITS_H