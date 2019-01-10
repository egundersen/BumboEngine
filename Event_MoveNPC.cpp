#include "Event_MoveNPC.h"

Event_MoveNPC::Event_MoveNPC(int unique_object_ID, int center_position_x, int center_position_y, int collider_width, int collider_height, int ending_position, char axis, int speed, char direction, int moved_character_ID, bool repeatable, std::vector<std::vector<std::pair<int, int>>>& element_has_object, Matrix & screen_matrix, std::vector<CharacterBase*>& characters, ScreenPosition & screen_position, int screen_width, int screen_height, int teleported_position_x, int teleported_position_y)
	: EventBase(unique_object_ID, center_position_x, center_position_y, collider_width, collider_height, 0, repeatable, element_has_object, screen_matrix, characters, screen_position, screen_width, screen_height), ending_position_{ ending_position }, axis_{ axis }, moved_character_ID_{ moved_character_ID }, direction_{ direction }, speed_{ speed }, teleported_position_x_{ teleported_position_x }, teleported_position_y_{ teleported_position_y }
{
}

void Event_MoveNPC::createEvent()
{
	updateColliderCoordinates();
}

void Event_MoveNPC::refreshEvent()
{
	switch (getEventIndex()) {
	case 0:
		if (getCharacterByID(moved_character_ID_)->getMovementIndex() == 0)
			getCharacterByID(moved_character_ID_)->move(ending_position_, axis_, speed_);
		else
			progressEvent();
		break;
	case 1:
		getCharacterByID(moved_character_ID_)->faceDirection(direction_);
		if (teleported_position_x_ != -1 && teleported_position_y_ != -1)
			getCharacterByID(moved_character_ID_)->teleportNPC(teleported_position_x_, teleported_position_y_);
		onEventOver();
		break;
	}
}