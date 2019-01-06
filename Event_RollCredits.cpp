#include "Event_RollCredits.h"

Event_RollCredits::Event_RollCredits(int unique_object_ID, bool &should_roll_credits, std::vector<std::vector<std::pair<int, int>>> &element_has_object, Matrix &screen_matrix, std::vector<CharacterBase*> &characters, ScreenPosition &screen_position, int screen_width, int screen_height)
	: EventBase(unique_object_ID, 198, 165, 3, 3, 0, true, element_has_object, screen_matrix, characters, screen_position, screen_width, screen_height), should_roll_credits_{ should_roll_credits }
{

}

void Event_RollCredits::createEvent()
{
	updateColliderCoordinates();
}

void Event_RollCredits::refreshEvent()
{
	should_roll_credits_ = true;
	onEventOver();
}