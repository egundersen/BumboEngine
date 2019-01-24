#ifndef EVENT_STOPAUDIO_H
#define EVENT_STOPAUDIO_H

#include "EventBase.h"

// Stops an audio track
class Event_StopAudio : public EventBase
{
public:
	Event_StopAudio(int unique_object_ID, int center_position_x, int center_position_y, int collider_width, int collider_height, std::string audio_ID, int character_ID,
		bool repeatable, std::vector<std::vector<std::pair<int, int>>> &element_has_object, Matrix &screen_matrix, std::vector<CharacterBase*> &characters, ScreenPosition &screen_position, int screen_width, int screen_height);

	void createEvent();
	void refreshEvent();
private:
	std::string audio_ID_;
};

#endif // !EVENT_STOPAUDIO_H
