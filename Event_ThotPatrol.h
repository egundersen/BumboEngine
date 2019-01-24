#ifndef EVENT_THOTPATROL_H
#define EVENT_THOTPATROL_H

#include "EventBase.h"

// Thot Patrol show up and challenge player to a fight
class Event_ThotPatrol : public EventBase
{
public:
	Event_ThotPatrol(int unique_object_ID, int center_position_x, int center_position_y, int collider_width, int collider_height, std::string player_name, CharacterBase *&selected_character,
		bool repeatable, std::vector<std::vector<std::pair<int, int>>> &element_has_object, Matrix &screen_matrix, std::vector<CharacterBase*> &characters, ScreenPosition &screen_position, int screen_width, int screen_height);

	void createEvent();
	void refreshEvent();
private:
	void moveToPlayer();
	void speak();
	void battle();

	CharacterBase *&selected_character_;
	std::string player_name_;
};

#endif // !EVENT_THOTPATROL_H