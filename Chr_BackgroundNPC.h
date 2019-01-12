#ifndef CHR_BACKGROUNDNPC_H
#define CHR_BACKGROUNDNPC_H

#include "CharacterBase.h"

class Chr_BackgroundNPC : public CharacterBase
{
public:
	Chr_BackgroundNPC(int center_position_x, int center_position_y, int unique_object_ID, PlayerDefinition &player, int screen_width, int screen_height, Matrix &world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object,  Matrix &screen_matrix, BitmapDefinition &bitmap, AudioDefinition &audio,
		// START CONFIGURABLE VARIABLES HERE -------------------------------------------------

		// Basic Popup Dialog (Only used if use_basic_dialog == TRUE)
		PopupDefinition popup_sprite,

		/* Sets the sprite ascii for the NPC world sprite */
		WorldSpriteContainer world_sprite,

		// Direction the NPC is facing
		char direction)

		: CharacterBase(center_position_x, center_position_y, popup_sprite, unique_object_ID, world_matrix, element_has_object, screen_matrix, screen_width, screen_height, 0, player, BossFightDefinition(), false, true, bitmap, audio, world_sprite)
	{
		faceDirection(direction);
	}

	Chr_BackgroundNPC(int center_position_x, int center_position_y, int unique_object_ID, WorldSpriteContainer world_sprite, char direction, PlayerDefinition &player, int screen_width, int screen_height, Matrix &world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object, Matrix &screen_matrix, BitmapDefinition &bitmap, AudioDefinition &audio)

		: CharacterBase(center_position_x, center_position_y, PopupDefinition(), unique_object_ID, world_matrix, element_has_object, screen_matrix, screen_width, screen_height, 0, player, BossFightDefinition(), false, true, bitmap, audio, world_sprite)
	{
		faceDirection(direction);
	}
};

#endif // !CHR_BACKGROUNDNPC_H
