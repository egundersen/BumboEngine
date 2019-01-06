#include "Event_SetupEnding.h"

Event_SetupEnding::Event_SetupEnding(int unique_object_ID, int center_position_x, int center_position_y, int collider_width, int collider_height, int teleported_coordinate_x, int teleported_coordinate_y, int character_ID, bool repeatable, std::vector<std::vector<std::pair<int, int>>>& element_has_object, Matrix & screen_matrix, std::vector<CharacterBase*>& characters, ScreenPosition & screen_position, int screen_width, int screen_height)
	: EventBase(unique_object_ID, center_position_x, center_position_y, collider_width, collider_height, character_ID, repeatable, element_has_object, screen_matrix, characters, screen_position, screen_width, screen_height), teleported_coordinated_y_{ teleported_coordinate_y }, teleported_coordinated_x_{ teleported_coordinate_x }
{

}

void Event_SetupEnding::createEvent()
{
	updateColliderCoordinates();
}

void Event_SetupEnding::refreshEvent()
{
	if (getCharacterByID(22) == nullptr) {
		getCharacterByID(50)->teleportNPC(913, 73);
		getCharacterByID(50)->faceDirection('r');
	}
	teleportPlayer(teleported_coordinated_x_, teleported_coordinated_y_);
	onEventOver();
}