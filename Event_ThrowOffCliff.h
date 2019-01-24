#ifndef EVENT_THROWOFFCLIFF_H
#define EVENT_THROWOFFCLIFF_H

#include "EventBase.h"

// Checkpoint guard "throws" an NPC off the cliff
class Event_ThrowOffCliff : public EventBase
{
public:
	Event_ThrowOffCliff(int unique_object_ID, int center_position_x, int center_position_y, int collider_width, int collider_height, int character_ID, std::string directory, bool repeatable,
		std::vector<std::vector<std::pair<int, int>>> &element_has_object, Matrix &screen_matrix, std::vector<CharacterBase*> &characters, ScreenPosition &screen_position, int screen_width, int screen_height);

	void createEvent();
	void refreshEvent();
private:
	void speak1();
	void move();
	void speak2();
	void throwOffCliff();

	int go_down_iterator_, fall_speed_;
	std::string directory_;
};

#endif // !EVENT_THROWOFFCLIFF_H