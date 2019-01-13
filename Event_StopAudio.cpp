#include "Event_StopAudio.h"

Event_StopAudio::Event_StopAudio(int unique_object_ID, int center_position_x, int center_position_y, int collider_width, int collider_height, std::string audio_ID, int character_ID, bool repeatable, std::vector<std::vector<std::pair<int, int>>>& element_has_object, Matrix & screen_matrix, std::vector<CharacterBase*>& characters, ScreenPosition & screen_position, int screen_width, int screen_height)
	: EventBase(unique_object_ID, center_position_x, center_position_y, collider_width, collider_height, character_ID, repeatable, element_has_object, screen_matrix, characters, screen_position, screen_width, screen_height), audio_ID_{ audio_ID }
{
}

void Event_StopAudio::createEvent()
{
	updateColliderCoordinates();
}

void Event_StopAudio::refreshEvent()
{
	std::string stop = "stop " + audio_ID_;
	std::string close = "close " + audio_ID_;

	std::wstring stopTemp = std::wstring(stop.begin(), stop.end());
	std::wstring closeTemp = std::wstring(close.begin(), close.end());

	TCHAR * stopTemp2 = (wchar_t *)stopTemp.c_str();
	TCHAR * closeTemp2 = (wchar_t *)closeTemp.c_str();

	mciSendString(stopTemp2, NULL, 0, NULL);
	mciSendString(closeTemp2, NULL, 0, NULL);

	onEventOver();
}
