#include "CharacterBase.h"
#include <Windows.h>

CharacterBase::CharacterBase(int center_position_x, int center_position_y, int popup_width, int popup_height, int unique_object_ID, std::vector<std::vector<char>>& world_matrix, std::vector<std::vector<std::pair<int, int>>>& element_has_object, std::vector<std::vector<std::string>>& matrix_display, int screen_width, int screen_height, std::string basic_dialog, char border_character)
	: Popup(center_position_x, center_position_y + 1, popup_width, popup_height, unique_object_ID, basic_dialog, world_matrix, element_has_object, matrix_display, screen_width, screen_height, border_character), use_basic_dialog_{ false },
	sprite_{ 12, 10, matrix_display, world_matrix }, has_begun_moving_{ false }, start_time_move_one_space_(0), start_time_move_(0), movement_direction_multiplier_(1), moving_direction_{ 'l' }, facing_direction_{ 'd' }, has_reached_destination_{ false }
{
	// Decide whether to use advance dialog or basic popup-styled dialog
	if (basic_dialog != "")
		use_basic_dialog_ = true;
}

CharacterBase::~CharacterBase()
{
	eraseSpriteAndColliders();
}

// draws the character sprite on the world matrix
void CharacterBase::createWorldSprite()
{
	// moving
	Image *up_1 = new Image("   @@@@   Z  XXX@@X  Z   XXXX   Z O#XXXX#O ZO ######O Z  %U  U%  Z");
	Image *down_1 = new Image("   @@@@   Z  X[][]X  Z   XXXX   Z O#XXXX#O ZO ######O Z  %U  U%  Z");
	Image *right_1 = new Image("   @@@@   Z  @@X[]X  Z   @XXX   Z  O#XX#O  Z  O%###%O Z   %%  %  Z");
	Image *left_1 = new Image("   @@@@   Z  X[]X@@  Z   XXX@   Z  O#XX#O  Z O%###%O  Z  %  %%   Z");
	Image *up_2 = new Image("   @@@@   Z  XXX@@X  Z   XXXX   Z O#XXXX#O Z O###### OZ  %U  U%  Z");
	Image *down_2 = new Image("   @@@@   Z  X[][]X  Z   XXXX   Z O#XXXX#O Z O###### OZ  %U  U%  Z");
	Image *right_2 = new Image("   @@@@   Z  @@X[]X  Z   @XXX O Z  O#XX#O  Z %%O#%#   Z %=  %%   Z");
	Image *left_2 = new Image("   @@@@   Z  X[]X@@  Z O XXX@   Z  O#XX#O  Z   #%#O%% Z   %%  =% Z");

	// Not moving
	Image *up_s = new Image("   @@@@   Z  XXX@@X  Z   XXXX   Z O#XXXX#O Z O######O Z  %U  U%  Z");
	Image *down_s = new Image("   @@@@   Z  X[][]X  Z   XXXX   Z O#XXXX#O Z O######O Z  %U  U%  Z");
	Image *right_s = new Image("   @@@@   Z  @@X[]X  Z   @XXX   Z  O#XX#O  Z  ######O Z  %U  U%  Z");
	Image *left_s = new Image("   @@@@   Z  X[]X@@  Z   XXX@   Z  O#XX#O  Z O######  Z  %U  U%  Z");

	sprite_states_.push_back(up_1);
	sprite_states_.push_back(down_1);
	sprite_states_.push_back(left_1);
	sprite_states_.push_back(right_1);
	sprite_states_.push_back(up_2);
	sprite_states_.push_back(down_2);
	sprite_states_.push_back(left_2);
	sprite_states_.push_back(right_2);
	sprite_states_.push_back(up_s);
	sprite_states_.push_back(down_s);
	sprite_states_.push_back(left_s);
	sprite_states_.push_back(right_s);

	sprite_.initializeSprites(sprite_states_);
	sprite_.setDirection(facing_direction_);
	sprite_.displaySprite(center_position_x_ - sprite_.getWidth() / 2 + 1, center_position_y_ - sprite_.getHeight() / 2 + 1);

	collider_height_ = sprite_.getHeight() - 2;
	collider_width_ = sprite_.getWidth() - 2;
	setObjectID();
	updateColliderCoordinates();
}

// Refreshes and shows basic popop
void CharacterBase::refreshPopup(char player_facing_direction)
{
	facing_direction_ = player_facing_direction;
	updateWorldSprite(facing_direction_);
	displayPopup();
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
				moving_direction_ = 'd';
			}
			else
			{
				movement_direction_multiplier_ = 1;
				moving_direction_ = 'u';
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
			(center_position_x_++) * movement_direction_multiplier_;
		}
		else
		{
			(center_position_y_++) * movement_direction_multiplier_;
		}
		updateColliderCoordinates();
		updateWorldSprite(moving_direction_);
		start_time_move_one_space_ = GetTickCount();
	}

	if (center_position_x_ == ending_position)
	{
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
