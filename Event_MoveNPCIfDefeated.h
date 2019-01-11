#ifndef EVENT_MOVENPCIFDEFEATED_H
#define EVENT_MOVENPCIFDEFEATED_H

#include "EventBase.h"

class Event_MoveNPCIfDefeated : public EventBase
{
public:
	Event_MoveNPCIfDefeated(int unique_object_ID, int center_position_x, int center_position_y, int collider_width, int collider_height, int teleported_coordinate_x, int teleported_coordinate_y, int moved_character_ID,
		int defeated_character_ID, bool allow_spare,
		bool repeatable, std::vector<std::vector<std::pair<int, int>>> &element_has_object, Matrix &screen_matrix, std::vector<CharacterBase*> &characters, ScreenPosition &screen_position, int screen_width, int screen_height);

	void createEvent();
	void refreshEvent();
	bool isAvailable();
private:
	int teleported_coordinated_x_, teleported_coordinated_y_, moved_character_ID_, defeated_character_ID_;
	bool allow_spare_;
};

#endif // !EVENT_MOVENPCIFDEFEATED_H