#include "CharacterBase.h"
#include <Windows.h>

CharacterBase::CharacterBase(int center_position_x, int center_position_y, PopupDefinition popup_sprite, int unique_object_ID, std::vector<std::vector<char>>& world_matrix, std::vector<std::vector<std::pair<int, int>>>& element_has_object, std::vector<std::vector<std::string>>& matrix_display, int screen_width, int screen_height, int event_ID, int &player_health, BossFightDefinition boss_fight_definition, bool attack_on_sight, bool use_basic_dialog, std::pair<std::string, int> &image_file_path, WorldSprite world_sprite)
	: PopupWithCollision(center_position_x, center_position_y + 1, popup_sprite, unique_object_ID, world_matrix, element_has_object, matrix_display, screen_width, screen_height), event_ID_{ event_ID }, use_basic_dialog_{ use_basic_dialog }, world_sprite_{ world_sprite },
	sprite_{ 12, 10, matrix_display, world_matrix }, has_begun_moving_{ false }, start_time_move_one_space_(0), start_time_move_(0), movement_direction_multiplier_(1), moving_direction_{ 'l' }, facing_direction_{ 'd' }, has_reached_destination_{ false }, attack_on_sight_{ attack_on_sight },
	BattleBase(screen_width, screen_height, matrix_display, player_health, boss_fight_definition, image_file_path), DialogManager(screen_width - 10, 9, screen_width, screen_height, matrix_display),
	screen_width_{ screen_width }, screen_height_{ screen_height }, matrix_display_{ matrix_display }, player_health_{ player_health }, movement_index_(0)
{
}

CharacterBase::~CharacterBase()
{
	eraseSpriteAndColliders();
}

// draws the character sprite on the world matrix
void CharacterBase::createWorldSprite()
{
	sprite_states_.push_back(world_sprite_.up_1);
	sprite_states_.push_back(world_sprite_.down_1);
	sprite_states_.push_back(world_sprite_.left_1);
	sprite_states_.push_back(world_sprite_.right_1);
	sprite_states_.push_back(world_sprite_.up_2);
	sprite_states_.push_back(world_sprite_.down_2);
	sprite_states_.push_back(world_sprite_.left_2);
	sprite_states_.push_back(world_sprite_.right_2);
	sprite_states_.push_back(world_sprite_.up_s);
	sprite_states_.push_back(world_sprite_.down_s);
	sprite_states_.push_back(world_sprite_.left_s);
	sprite_states_.push_back(world_sprite_.right_s);

	sprite_.initializeSprites(sprite_states_);
	sprite_.setDirection(facing_direction_);
	sprite_.displaySprite(center_position_x_ - sprite_.getWidth() / 2 + 1, center_position_y_ - sprite_.getHeight() / 2 + 1);

	collider_height_ = sprite_.getHeight() - 2;
	collider_width_ = sprite_.getWidth() - 2;
	setObjectID();
	updateColliderCoordinates();
}

// Refreshes and shows basic popop
void CharacterBase::refreshPopup()
{
	displayPopup(0, 0);
}

void CharacterBase::faceDirection(char player_facing_direction)
{
	facing_direction_ = player_facing_direction;
	updateWorldSprite(facing_direction_);
}

// Resets all parts of the character (Except for the world dialog)
void CharacterBase::reset()
{
	resetAttackPatterns();
	resetBattleSpace();
}

// Resets/Initializes all parts of the character
void CharacterBase::initializeCharacter()
{
	setDialogNodes();
	reset();
}

void CharacterBase::resetAttackPatterns()
{
	// Erase all attacks (If attacks exist)
	for (std::vector< AttackPatternBase* >::iterator it = attack_patterns_.begin(); it != attack_patterns_.end(); ++it)
	{
		delete (*it);
	}
	attack_patterns_.clear();

	// Add all attacks
	initializeAttackPatterns(screen_width_, screen_height_, matrix_display_, player_health_);
}

// Change location and/or direction of world sprite
void CharacterBase::updateWorldSprite(char direction)
{
	sprite_.setDirection(direction);
	sprite_.displaySprite(center_position_x_ - sprite_.getWidth() / 2 + 1, center_position_y_ - sprite_.getHeight() / 2 + 1);
}

// Move to designated position (Can only move per x-axis or per y-axis)
void CharacterBase::move(int ending_position, char axis, int speed)
{
	if (!has_begun_moving_)
	{
		has_reached_destination_ = false; // <=== Deprecated
		start_time_move_one_space_ = GetTickCount();
		if (axis == 'x')
		{
			if (ending_position - center_position_x_ < 0)
			{
				movement_direction_multiplier_ = -1;
				moving_direction_ = 'l';
			}
			else
			{
				movement_direction_multiplier_ = 1;
				moving_direction_ = 'r';
			}
		}
		else
		{
			if (ending_position - center_position_y_ < 0)
			{
				movement_direction_multiplier_ = -1;
				moving_direction_ = 'u';
			}
			else
			{
				movement_direction_multiplier_ = 1;
				moving_direction_ = 'd';
			}
		}
		has_begun_moving_ = true;
	}

	double current_time_move = GetTickCount() - start_time_move_one_space_;
	if (current_time_move > speed)
	{
		eraseOldColliders();
		if (axis == 'x')
		{
			if (movement_direction_multiplier_ == -1)
				center_position_x_--;
			else
				center_position_x_++;
		}
		else
		{
			if (movement_direction_multiplier_ == -1)
				center_position_y_--;
			else
				center_position_y_++;
		}
		updateColliderCoordinates();
		updateWorldSprite(moving_direction_);
		start_time_move_one_space_ = GetTickCount();
	}

	if (center_position_x_ == ending_position || center_position_y_ == ending_position)
	{
		has_begun_moving_ = false;
		movement_index_++;
		has_reached_destination_ = true;
	}
}

// Teleports NPC to given coordinates
void CharacterBase::teleportNPC(int center_position_x, int center_position_y)
{
	eraseSpriteAndColliders();
	center_position_x_ = center_position_x;
	center_position_y_ = center_position_y;
	updateColliderCoordinates();
	updateWorldSprite(moving_direction_);
}

// Called when character is destroyed or removed from map
void CharacterBase::onDespawn()
{
	sprite_.removeSprite(center_position_x_ - sprite_.getWidth() / 2 + 1, center_position_y_ - sprite_.getHeight() / 2 + 1);
}

// Resets movement function, allowing movement function to be called again
void CharacterBase::resetMovingPath()
{
	has_begun_moving_ = false;
}

// Removes Sprite and Colliders from world map. Does not deallocate them!
void CharacterBase::eraseSpriteAndColliders()
{
	for (int i = 0; i < collider_height_; ++i)
		for (int j = 0; j < collider_width_; ++j)
		{
			world_matrix_[center_position_y_ - collider_height_ / 2 + i][center_position_x_ - collider_width_ / 2 + j] = ' ';
			element_has_object_[center_position_y_ - collider_height_ / 2 + i][center_position_x_ - collider_width_ / 2 + j].first = 0;
			element_has_object_[center_position_y_ - collider_height_ / 2 + i][center_position_x_ - collider_width_ / 2 + j].second = 0;
		}
}

// erases the edge of character's colliders based on their rotation. Ideal for moving character with little lag time
void CharacterBase::eraseOldColliders()
{
	switch (moving_direction_)
	{
	case 'u':
		for (int j = 0; j < collider_width_; ++j)
		{
			element_has_object_[center_position_y_ - collider_height_ / 2][center_position_x_ - collider_width_ / 2 + j].first = 0;
			element_has_object_[center_position_y_ - collider_height_ / 2][center_position_x_ - collider_width_ / 2 + j].second = 0;
		}
		break;
	case 'd':
		for (int j = 0; j < collider_width_; ++j)
		{
			element_has_object_[center_position_y_ - collider_height_ / 2 + collider_height_ - 1][center_position_x_ - collider_width_ / 2 + j].first = 0;
			element_has_object_[center_position_y_ - collider_height_ / 2 + collider_height_ - 1][center_position_x_ - collider_width_ / 2 + j].second = 0;
		}
		break;
	case 'r':
		for (int i = 0; i < collider_height_; ++i)
		{
			element_has_object_[center_position_y_ - collider_height_ / 2 + i][center_position_x_ - collider_width_ / 2].first = 0;
			element_has_object_[center_position_y_ - collider_height_ / 2 + i][center_position_x_ - collider_width_ / 2].second = 0;
		}
		break;
	case 'l':
		for (int i = 0; i < collider_height_; ++i)
		{
			element_has_object_[center_position_y_ - collider_height_ / 2 + i][center_position_x_ - collider_width_ / 2 + collider_width_ - 1].first = 0;
			element_has_object_[center_position_y_ - collider_height_ / 2 + i][center_position_x_ - collider_width_ / 2 + collider_width_ - 1].second = 0;
		}
		break;
	default:
		break;
	}
}
