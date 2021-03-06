#include "Event_MoveNPCIfDefeated.h"

Event_MoveNPCIfDefeated::Event_MoveNPCIfDefeated(int unique_object_ID, int center_position_x, int center_position_y, int collider_width, int collider_height, int teleported_coordinate_x, int teleported_coordinate_y, int moved_character_ID, int defeated_character_ID, bool allow_spare, bool repeatable, std::vector<std::vector<std::pair<int, int>>>& element_has_object, Matrix & screen_matrix, std::vector<CharacterBase*>& characters, ScreenPosition & screen_position, int screen_width, int screen_height)
	: EventBase(unique_object_ID, center_position_x, center_position_y, collider_width, collider_height, 0, repeatable, element_has_object, screen_matrix, characters, screen_position, screen_width, screen_height), teleported_coordinated_y_{ teleported_coordinate_y }, teleported_coordinated_x_{ teleported_coordinate_x }, moved_character_ID_{ moved_character_ID }, defeated_character_ID_{ defeated_character_ID }, allow_spare_{ allow_spare }
{
}

void Event_MoveNPCIfDefeated::createEvent()
{
	updateColliderCoordinates();
}

void Event_MoveNPCIfDefeated::refreshEvent()
{
	if (getCharacterByID(moved_character_ID_) == nullptr) { onEventOver(); return; }

	getCharacterByID(moved_character_ID_)->teleportNPC(teleported_coordinated_x_, teleported_coordinated_y_);
	onEventOver();
}

bool Event_MoveNPCIfDefeated::isAvailable()
{
	if (getCharacterByID(defeated_character_ID_) == nullptr)
		return true;
	else if (allow_spare_ && getCharacterByID(defeated_character_ID_)->isBattleOver())
		return true;
	else
		return false;
}
