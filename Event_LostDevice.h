#ifndef EVENT_LOSTDEVICE_H
#define EVENT_LOSTDEVICE_H

#include "EventBase.h"

class Event_LostDevice : public EventBase
{
public:
	Event_LostDevice(int unique_object_ID, int center_position_x, int center_position_y, int collider_width, int collider_height, std::string player_name,
		bool repeatable, std::vector<std::vector<std::pair<int, int>>> &element_has_object, Matrix &screen_matrix, std::vector<CharacterBase*> &characters, ScreenPosition &screen_position, int screen_width, int screen_height);

	void createEvent();
	void refreshEvent();
private:
	void alignToPlayer();
	void lookAround();
	void moveToPlayer();
	void freakOut();
	void spin();
	void giveInstructions();
	void leave();

	std::string player_name_;
};

#endif // !EVENT_LOSTDEVICE_H