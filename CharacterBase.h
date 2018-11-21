#include "MatrixBase.h"
#include "DialogManager.h"
#include "DialogNode.h"
#include "BattleBase.h"
#include "PopupWithCollision.h"
#include "NPCSprite.h"

#ifndef CHARACTERBASE_H
#define CHARACTERBASE_H

class CharacterBase : public PopupWithCollision, public BattleBase, public DialogManager
{
public:
	CharacterBase(int center_position_x, int center_position_y, int popup_width, int popup_height, int unique_object_ID,
		std::vector<std::vector<char>> &world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object,
		std::vector<std::vector<std::string>> &matrix_display, int screen_width, int screen_height, int event_ID,

		std::string basic_dialog, char border_character, 
		
		int &player_health, int boss_health, std::string boss_name, std::string boss_ascii_art, std::string ascii_overlay,
		int overlay_x, int overlay_y);
	~CharacterBase();

	// World Map Sprite
	void createWorldSprite(); // Sprite in world map
	void updateWorldSprite(char direction);

	// Movement
	void resetMovingPath();
	void move(int ending_position, char axis, int speed);
	void teleportNPC(int center_position_x, int center_position_y);
	void onDespawn();

	int eventID() { return event_ID_; }
	bool hasReachDestination() { return has_reached_destination_; }
	int getCenterPositionX() { return center_position_x_; }
	int getCenterPositionY() { return center_position_y_; }

	// Basic Popup
	void refreshPopup();
	void faceDirection(char player_facing_direction);
	bool useBasicDialog() { return use_basic_dialog_; }
private:
	void eraseSpriteAndColliders();
	void eraseOldColliders();
	void setObjectID() { object_type_ID_ = 3; };

	NPCSprite sprite_;
	std::vector<Image*> sprite_states_;
	char facing_direction_, moving_direction_;
	bool use_basic_dialog_, has_begun_moving_, has_reached_destination_;
	int start_time_move_one_space_, start_time_move_, movement_direction_multiplier_, event_ID_;
};

#endif // !CHARACTERBASE_H
