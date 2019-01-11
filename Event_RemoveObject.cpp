#include "Event_RemoveObject.h"

Event_RemoveObject::Event_RemoveObject(int unique_object_ID, int center_position_x, int center_position_y, int collider_width, int collider_height, int object_coordinate_x, int object_coordinate_y, int object_width, int object_height, int character_ID, bool repeatable, Matrix &world_matrix, std::vector<std::vector<std::pair<int, int>>>& element_has_object, Matrix & screen_matrix, std::vector<CharacterBase*>& characters, ScreenPosition & screen_position, int screen_width, int screen_height)
	: EventBase(unique_object_ID, center_position_x, center_position_y, collider_width, collider_height, character_ID, repeatable, element_has_object, screen_matrix, characters, screen_position, screen_width, screen_height), object_coordinate_y_{ object_coordinate_y }, object_coordinate_x_{ object_coordinate_x }, object_width_{ object_width }, object_height_{ object_height }, world_matrix_{ world_matrix }
{
}

void Event_RemoveObject::createEvent()
{
	updateColliderCoordinates();
}

void Event_RemoveObject::refreshEvent()
{
	drawSolidRectangle(object_coordinate_x_ - object_width_ / 2, object_coordinate_y_ - object_height_ / 2, object_width_, object_height_, ' ', world_matrix_);
	onEventOver();
}
