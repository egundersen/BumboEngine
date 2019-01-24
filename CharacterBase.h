#ifndef CHARACTERBASE_H
#define CHARACTERBASE_H

#include "DialogManager.h"
#include "DialogNode.h"
#include "BattleBase.h"
#include "BattleSprite.h"
#include "NPCSprite.h"
#include "PopupWithCollision.h"
#include "WorldSpriteContainer.h"

// Manages basic functionality for NPCs, their location, moving them, their dialog/health, etc...
class CharacterBase : public PopupWithCollision, public BattleBase, public DialogManager
{
public:
	CharacterBase(int center_position_x, int center_position_y, PopupDefinition popup_sprite, int unique_object_ID,
		Matrix &world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object,
		Matrix &screen_matrix, int screen_width, int screen_height, int event_ID,

		PlayerDefinition &player, BossFightDefinition boss_fight_definition, bool attack_on_sight, bool use_basic_dialog, BitmapDefinition &bitmap,
		AudioDefinition &audio, WorldSpriteContainer world_sprite);
	~CharacterBase();

	// Initializes the character class (Must be called once)
	void initializeCharacter();

	// Attack On Sight Event
	bool shouldAttackOnSight() { return attack_on_sight_; }

	// World Sprite
	void createWorldSprite(); // Sprite in world map
	void updateWorldSprite(char direction);

	// World Sprite Movement
	void resetMovingPath();
	void move(int ending_position, char axis, int speed);
	void moveAndTeleport(int ending_position, char axis, int speed, char ending_direction, int center_position_x, int center_position_y);
	void waitForTime(int time);
	void teleportNPC(int center_position_x, int center_position_y);
	void onDespawn();
	void displayGhostSprite(int top_left_position_x, int top_left_position_y, char moving_direction);
	void DEBUG_eraseSpriteColliders();

	int eventID() { return event_ID_; }
	bool hasReachDestination() { return has_reached_destination_; }
	int getCenterPositionX() { return center_position_x_; }
	int getCenterPositionY() { return center_position_y_; }
	int getMovementIndex() { return movement_index_; }
	void incrementMovementIndex() { movement_index_++; }
	void resetDestination() { has_reached_destination_ = false; }
	void resetMovementIndex() { movement_index_ = 0; has_reached_destination_ = false; }

	// Basic Popup
	void refreshPopup();
	void faceDirection(char player_facing_direction);
	bool useBasicDialog() { return use_basic_dialog_; }

	// Reset and attack creation-related
	void reset();
protected:
	virtual void initializeAttackPatterns(int screen_width, int screen_height, Matrix &screen_matrix, PlayerDefinition &player) {}
	virtual void setUniqueAttributes() {}

	PlayerDefinition &player_;
private:
	void resetAttackPatterns();
	void eraseSpriteAndColliders();
	void eraseOldColliders();
	void setObjectID() { object_type_ID_ = 3; };

	WorldSpriteContainer world_sprite_;
	NPCSprite sprite_;
	
	std::vector<Image*> sprite_states_;
	char facing_direction_, moving_direction_;
	bool use_basic_dialog_, has_begun_moving_, has_reached_destination_, attack_on_sight_;
	int start_time_move_one_space_, start_time_move_, movement_direction_multiplier_, event_ID_,
		screen_width_, screen_height_, movement_index_;
	Matrix &screen_matrix_;
};

#endif // !CHARACTERBASE_H
