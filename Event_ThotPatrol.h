#ifndef EVENT_THOTPATROL_H
#define EVENT_THOTPATROL_H

#include "EventBase.h"

class Event_ThotPatrol : public EventBase
{
public:
	Event_ThotPatrol(int unique_object_ID, int center_position_x, int center_position_y, int collider_width, int collider_height, CharacterBase *&selected_character,
		bool repeatable, std::vector<std::vector<std::pair<int, int>>> &element_has_object, Matrix &screen_matrix, std::vector<CharacterBase*> &characters, ScreenPosition &screen_position, int screen_width, int screen_height);

	void createEvent();
	void refreshEvent();
private:
	void moveToPlayer();
	void speak();
	void battle();

	CharacterBase *&selected_character_;
};

#endif // !EVENT_THOTPATROL_H