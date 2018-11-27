#include "CharacterBase.h"
#include <string>

#ifndef CHR_BACKGROUNDNPC_H
#define CHR_BACKGROUNDNPC_H

class Chr_BackgroundNPC : public CharacterBase
{
public:
	Chr_BackgroundNPC(int center_position_x, int center_position_y, int &player_health, int unique_object_ID, int screen_width, int screen_height, std::vector<std::vector<char>> &world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object, std::vector<std::vector<std::string>> &matrix_display, std::pair<std::string, int> &image_file_path,
		// START CONFIGURABLE VARIABLES HERE -------------------------------------------------

		// Basic Popup Dialog (Only used if use_basic_dialog == TRUE)
		PopupDefinition popup_sprite,

		  /* Sets the sprite ascii for the NPC world sprite */
		WorldSprite world_sprite,

		char direction,

		/* Use Event at end of battle (Whether slay or spare is called) | Must match ID of an actual event in the events folder */
		int event_ID = 0) // 0 = no event

		: CharacterBase(center_position_x, center_position_y, popup_sprite, unique_object_ID, world_matrix, element_has_object, matrix_display, screen_width, screen_height, event_ID, player_health, BossFightDefinition(), false, true, image_file_path, world_sprite)
	{
		faceDirection(direction);
	}
};

#endif // !CHR_BACKGROUNDNPC_H
