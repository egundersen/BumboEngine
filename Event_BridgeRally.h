#ifndef EVENT_BRIDGERALLY_H
#define EVENT_BRIDGERALLY_H

#include "EventBase.h"

class Event_BridgeRally : public EventBase
{
public:
	Event_BridgeRally(int unique_object_ID, int center_position_x, int center_position_y, int collider_width, int collider_height, int character_ID,
		bool repeatable, Matrix &world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object, Matrix &screen_matrix, std::vector<CharacterBase*> &characters, ScreenPosition &screen_position, int screen_width, int screen_height);

	void createEvent();
	void refreshEvent();
private:
	void speak();
	void leave();

	Matrix & world_matrix_;
	Image rock_;
};

#endif // !EVENT_BRIDGERALLY_H