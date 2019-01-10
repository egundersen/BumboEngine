#ifndef EVENT_MOVENPC_H
#define EVENT_MOVENPC_H

#include "EventBase.h"

class Event_MoveNPC : public EventBase
{
public:
	Event_MoveNPC(int unique_object_ID, int center_position_x, int center_position_y, int collider_width, int collider_height, int ending_position, char axis, int speed, char direction, int moved_character_ID,
		bool repeatable, std::vector<std::vector<std::pair<int, int>>> &element_has_object, Matrix &screen_matrix, std::vector<CharacterBase*> &characters, ScreenPosition &screen_position, int screen_width, int screen_height, 
		int teleported_position_x = -1, int teleported_position_y = -1);

	void createEvent();
	void refreshEvent();
private:
	int ending_position_, moved_character_ID_, speed_, teleported_position_x_, teleported_position_y_;
	char direction_, axis_;
};

#endif // !EVENT_MOVENPC_H