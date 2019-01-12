#include "Sprite.h"

Sprite::Sprite(int sprite_width, int sprite_height, Matrix &screen_matrix)
	: sprite_width_{ sprite_width }, sprite_height_{ sprite_height }, screen_matrix_{ screen_matrix }, animation_position_(0), start_time_player_animation_(0),
	is_moving_vertically_{ false }, is_moving_horizontally{ false }, player_animation_speed_(240), direction_{'d'}, x_position_(0), y_position_(0),
	up_1_(sprite_width, sprite_height),
	up_2_(sprite_width, sprite_height),
	down_1_(sprite_width, sprite_height),
	down_2_(sprite_width, sprite_height),
	right_1_(sprite_width, sprite_height),
	right_2_(sprite_width, sprite_height),
	left_1_(sprite_width, sprite_height),
	left_2_(sprite_width, sprite_height),
	up_s_(sprite_width, sprite_height),
	down_s_(sprite_width, sprite_height),
	left_s_(sprite_width, sprite_height),
	right_s_(sprite_width, sprite_height)
{
	start_time_player_animation_ = GetTickCount64();
}

// Chooses what to display to the screen
void Sprite::displaySprite(int top_left_position_x, int top_left_position_y)
{
	if (!is_moving_vertically_ && !is_moving_horizontally)
	{
		switch (direction_)
		{
		case 'u':
			displaySpriteAtDirection(up_s_, top_left_position_x, top_left_position_y);
			break;
		case 'd':
			displaySpriteAtDirection(down_s_, top_left_position_x, top_left_position_y);
			break;
		case 'l':
			displaySpriteAtDirection(left_s_, top_left_position_x, top_left_position_y);
			break;
		case 'r':
			displaySpriteAtDirection(right_s_, top_left_position_x, top_left_position_y);
			break;
		default:
			break;
		}
	}
	else if (animation_position_ == 0)
	{
		switch (direction_)
		{
		case 'u':
			displaySpriteAtDirection(up_1_, top_left_position_x, top_left_position_y);
			break;
		case 'd':
			displaySpriteAtDirection(down_1_, top_left_position_x, top_left_position_y);
			break;
		case 'l':
			displaySpriteAtDirection(left_1_, top_left_position_x, top_left_position_y);
			break;
		case 'r':
			displaySpriteAtDirection(right_1_, top_left_position_x, top_left_position_y);
			break;
		default:
			break;
		}
	}
	else
	{
		switch (direction_)
		{
		case 'u':
			displaySpriteAtDirection(up_2_, top_left_position_x, top_left_position_y);
			break;
		case 'd':
			displaySpriteAtDirection(down_2_, top_left_position_x, top_left_position_y);
			break;
		case 'l':
			displaySpriteAtDirection(left_2_, top_left_position_x, top_left_position_y);
			break;
		case 'r':
			displaySpriteAtDirection(right_2_, top_left_position_x, top_left_position_y);
			break;
		default:
			break;
		}
	}

	animationCounter();
}

// Choose how to remove sprite from world matrix
void Sprite::removeSprite(int top_left_position_x, int top_left_position_y)
{
	if (!is_moving_vertically_ && !is_moving_horizontally)
	{
		switch (direction_)
		{
		case 'u':
			eraseSpriteAtDirection(up_s_, top_left_position_x, top_left_position_y);
			break;
		case 'd':
			eraseSpriteAtDirection(down_s_, top_left_position_x, top_left_position_y);
			break;
		case 'l':
			eraseSpriteAtDirection(left_s_, top_left_position_x, top_left_position_y);
			break;
		case 'r':
			eraseSpriteAtDirection(right_s_, top_left_position_x, top_left_position_y);
			break;
		default:
			break;
		}
	}
	else
	{
		switch (direction_)
		{
		case 'u':
			eraseSpriteAtDirection(up_1_, top_left_position_x, top_left_position_y);
			eraseSpriteAtDirection(up_2_, top_left_position_x, top_left_position_y);
			break;
		case 'd':
			eraseSpriteAtDirection(down_1_, top_left_position_x, top_left_position_y);
			eraseSpriteAtDirection(down_2_, top_left_position_x, top_left_position_y);
			break;
		case 'l':
			eraseSpriteAtDirection(left_1_, top_left_position_x, top_left_position_y);
			eraseSpriteAtDirection(left_2_, top_left_position_x, top_left_position_y);
			break;
		case 'r':
			eraseSpriteAtDirection(right_1_, top_left_position_x, top_left_position_y);
			eraseSpriteAtDirection(right_2_, top_left_position_x, top_left_position_y);
			break;
		default:
			break;
		}
	}
}

// Choose which direction to display ghost sprite
void Sprite::displayGhostSprite(int top_left_position_x, int top_left_position_y, int screen_width, int screen_height, char moving_direction)
{
	if (!is_moving_vertically_ && !is_moving_horizontally)
	{
		switch (moving_direction)
		{
		case 'u':
			displayGhostSpriteAtDirection(up_s_, top_left_position_x, top_left_position_y, screen_width, screen_height, 'u');
			break;
		case 'd':
			displayGhostSpriteAtDirection(down_s_, top_left_position_x, top_left_position_y, screen_width, screen_height, 'd');
			break;
		case 'l':
			displayGhostSpriteAtDirection(left_s_, top_left_position_x, top_left_position_y, screen_width, screen_height, 'l');
			break;
		case 'r':
			displayGhostSpriteAtDirection(right_s_, top_left_position_x, top_left_position_y, screen_width, screen_height, 'r');
			break;
		default:
			break;
		}
	}
	else if (animation_position_ == 0)
	{
		switch (moving_direction)
		{
		case 'u':
			displayGhostSpriteAtDirection(up_1_, top_left_position_x, top_left_position_y, screen_width, screen_height, 'u');
			break;
		case 'd':
			displayGhostSpriteAtDirection(down_1_, top_left_position_x, top_left_position_y, screen_width, screen_height, 'd');
			break;
		case 'l':
			displayGhostSpriteAtDirection(left_1_, top_left_position_x, top_left_position_y, screen_width, screen_height, 'l');
			break;
		case 'r':
			displayGhostSpriteAtDirection(right_1_, top_left_position_x, top_left_position_y, screen_width, screen_height, 'r');
			break;
		default:
			break;
		}
	}
	else
	{
		switch (moving_direction)
		{
		case 'u':
			displayGhostSpriteAtDirection(up_2_, top_left_position_x, top_left_position_y, screen_width, screen_height, 'u');
			break;
		case 'd':
			displayGhostSpriteAtDirection(down_2_, top_left_position_x, top_left_position_y, screen_width, screen_height, 'd');
			break;
		case 'l':
			displayGhostSpriteAtDirection(left_2_, top_left_position_x, top_left_position_y, screen_width, screen_height, 'l');
			break;
		case 'r':
			displayGhostSpriteAtDirection(right_2_, top_left_position_x, top_left_position_y, screen_width, screen_height, 'r');
			break;
		default:
			break;
		}
	}
}

// Decide whether sprite should use "moving" animation
void Sprite::setMoving(std::string direction)
{
	if (direction == "verticle")
		is_moving_vertically_ = true;
	else if (direction == "not verticle")
		is_moving_vertically_ = false;
	else if (direction == "horizontal")
		is_moving_horizontally = true;
	else
		is_moving_horizontally = false;
}

// Changes player animation every 'X' seconds
void Sprite::animationCounter()
{
	double current_time_move_player = GetTickCount64() - start_time_player_animation_;
	if (current_time_move_player >= player_animation_speed_)
	{
		if (animation_position_ == 0)
			animation_position_ = 1;
		else
			animation_position_ = 0;
		start_time_player_animation_ = GetTickCount64();
	}
}