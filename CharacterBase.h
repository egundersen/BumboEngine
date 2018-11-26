#include "MatrixBase.h"
#include "DialogManager.h"
#include "DialogNode.h"
#include "BattleBase.h"
#include "PopupWithCollision.h"
#include "NPCSprite.h"
#include "WorldSprite.h"

#ifndef CHARACTERBASE_H
#define CHARACTERBASE_H

class CharacterBase : public PopupWithCollision, public BattleBase, public DialogManager
{
public:
	CharacterBase(int center_position_x, int center_position_y, PopupDefinition popup_sprite, int unique_object_ID,
		std::vector<std::vector<char>> &world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object,
		std::vector<std::vector<std::string>> &matrix_display, int screen_width, int screen_height, int event_ID,

		int &player_health, BossFightDefinition boss_fight_definition, bool attack_on_sight, bool use_basic_dialog, std::pair<std::string, int> &image_file_path,
		WorldSprite world_sprite);
	~CharacterBase();

	// Initializes the character class (Must be called once)
	void initializeCharacter();

	// Attack On Sight Event
	bool shouldAttackOnSight() { return attack_on_sight_; }

	// World Map Sprite
	void createWorldSprite(); // Sprite in world map
	void updateWorldSprite(char direction);
	NPCSprite *getSprite() { return &sprite_; }

	// World Movement
	void resetMovingPath();
	void move(int ending_position, char axis, int speed);
	void teleportNPC(int center_position_x, int center_position_y);
	void onDespawn();

	int eventID() { return event_ID_; }
	bool hasReachDestination() { return has_reached_destination_; }
	int getCenterPositionX() { return center_position_x_; }
	int getCenterPositionY() { return center_position_y_; }
	int getMovementIndex() { return movement_index_; }

	// Basic Popup
	void refreshPopup();
	void faceDirection(char player_facing_direction);
	bool useBasicDialog() { return use_basic_dialog_; }

	// Reset and attack creation-related
	void reset();
protected:
	virtual void initializeAttackPatterns(int screen_width, int screen_height, std::vector<std::vector<std::string>> &matrix_display, int &player_health) {}
private:
	void resetAttackPatterns();
	void eraseSpriteAndColliders();
	void eraseOldColliders();
	void setObjectID() { object_type_ID_ = 3; };

	WorldSprite world_sprite_;
	NPCSprite sprite_;
	std::vector<Image*> sprite_states_;
	char facing_direction_, moving_direction_;
	bool use_basic_dialog_, has_begun_moving_, has_reached_destination_, attack_on_sight_;
	int start_time_move_one_space_, start_time_move_, movement_direction_multiplier_, event_ID_,
		screen_width_, screen_height_, &player_health_, movement_index_;
	std::vector<std::vector<std::string>> &matrix_display_;
};

#endif // !CHARACTERBASE_H
