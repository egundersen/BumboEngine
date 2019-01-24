#ifndef EVENT_REMOVEOBJECT_H
#define EVENT_REMOVEOBJECT_H

#include "EventBase.h"

// Removes an object from the world matrix
class Event_RemoveObject : public EventBase
{
public:
	Event_RemoveObject(int unique_object_ID, int center_position_x, int center_position_y, int collider_width, int collider_height, int object_coordinate_x, int object_coordinate_y, int object_width, int object_height, int character_ID,
		bool repeatable, Matrix &world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object, Matrix &screen_matrix, std::vector<CharacterBase*> &characters, ScreenPosition &screen_position, int screen_width, int screen_height);

	void createEvent();
	void refreshEvent();
private:
	int object_coordinate_x_, object_coordinate_y_, object_width_, object_height_;
	Matrix &world_matrix_;
};

#endif // !EVENT_REMOVEOBJECT_H
