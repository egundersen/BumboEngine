#ifndef EVENT_TELEPORTPLAYER_H
#define EVENT_TELEPORTPLAYER_H

#include "EventBase.h"

// Teleports player to designated coordinates
class Event_TeleportPlayer : public EventBase
{
public:
	Event_TeleportPlayer(int unique_object_ID, int center_position_x, int center_position_y, int collider_width, int collider_height, int teleported_coordinate_x, int teleported_coordinate_y, int character_ID, bool repeatable,
		std::vector<std::vector<std::pair<int, int>>> &element_has_object, Matrix &screen_matrix, std::vector<CharacterBase*> &characters, ScreenPosition &screen_position, int screen_width, int screen_height);

	void createEvent();
	void refreshEvent();
private:
	int teleported_coordinated_x_, teleported_coordinated_y_;
};

#endif // !EVENT_TELEPORTPLAYER_H
