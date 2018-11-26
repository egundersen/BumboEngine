#include "Sprite.h"
#include <Windows.h>

Sprite::Sprite(int sprite_width, int sprite_height, std::vector<std::vector<std::string>> &matrix_display)
	: sprite_width_{ sprite_width }, sprite_height_{ sprite_height }, matrix_display_{ matrix_display }, animation_position_(0), start_time_player_animation_(0),
	is_moving_vertically_{ false }, is_moving_horizontally{ false }, player_animation_speed_(240), direction_{'d'},
	up_1_(sprite_height_, std::vector<char>(sprite_width_, ' ')),
	up_2_(sprite_height_, std::vector<char>(sprite_width_, ' ')),
	down_1_(sprite_height_, std::vector<char>(sprite_width_, ' ')),
	down_2_(sprite_height_, std::vector<char>(sprite_width_, ' ')),
	right_1_(sprite_height_, std::vector<char>(sprite_width_, ' ')),
	right_2_(sprite_height_, std::vector<char>(sprite_width_, ' ')),
	left_1_(sprite_height_, std::vector<char>(sprite_width_, ' ')),
	left_2_(sprite_height_, std::vector<char>(sprite_width_, ' ')),
	up_s_(sprite_height_, std::vector<char>(sprite_width_, ' ')),
	down_s_(sprite_height_, std::vector<char>(sprite_width_, ' ')),
	left_s_(sprite_height_, std::vector<char>(sprite_width_, ' ')),
	right_s_(sprite_height_, std::vector<char>(sprite_width_, ' '))
{
	start_time_player_animation_ = GetTickCount();
}

// Chooses what to display to the screen
void Sprite::displaySprite(int position_x, int position_y)
{
	if (!is_moving_vertically_ && !is_moving_horizontally)
	{
		switch (direction_)
		{
		case 'u':
			displaySpriteAtDirection(up_s_, position_y, position_x);
			break;
		case 'd':
			displaySpriteAtDirection(down_s_, position_y, position_x);
			break;
		case 'l':
			displaySpriteAtDirection(left_s_, position_y, position_x);
			break;
		case 'r':
			displaySpriteAtDirection(right_s_, position_y, position_x);
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
			displaySpriteAtDirection(up_1_, position_y, position_x);
			break;
		case 'd':
			displaySpriteAtDirection(down_1_, position_y, position_x);
			break;
		case 'l':
			displaySpriteAtDirection(left_1_, position_y, position_x);
			break;
		case 'r':
			displaySpriteAtDirection(right_1_, position_y, position_x);
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
			displaySpriteAtDirection(up_2_, position_y, position_x);
			break;
		case 'd':
			displaySpriteAtDirection(down_2_, position_y, position_x);
			break;
		case 'l':
			displaySpriteAtDirection(left_2_, position_y, position_x);
			break;
		case 'r':
			displaySpriteAtDirection(right_2_, position_y, position_x);
			break;
		default:
			break;
		}
	}

	animationCounter();
}

void Sprite::removeSprite(int position_x, int position_y)
{
	if (!is_moving_vertically_ && !is_moving_horizontally)
	{
		switch (direction_)
		{
		case 'u':
			eraseSpriteAtDirection(up_s_, position_y, position_x);
			break;
		case 'd':
			eraseSpriteAtDirection(down_s_, position_y, position_x);
			break;
		case 'l':
			eraseSpriteAtDirection(left_s_, position_y, position_x);
			break;
		case 'r':
			eraseSpriteAtDirection(right_s_, position_y, position_x);
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
			eraseSpriteAtDirection(up_1_, position_y, position_x);
			break;
		case 'd':
			eraseSpriteAtDirection(down_1_, position_y, position_x);
			break;
		case 'l':
			eraseSpriteAtDirection(left_1_, position_y, position_x);
			break;
		case 'r':
			eraseSpriteAtDirection(right_1_, position_y, position_x);
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
			eraseSpriteAtDirection(up_2_, position_y, position_x);
			break;
		case 'd':
			eraseSpriteAtDirection(down_2_, position_y, position_x);
			break;
		case 'l':
			eraseSpriteAtDirection(left_2_, position_y, position_x);
			break;
		case 'r':
			eraseSpriteAtDirection(right_2_, position_y, position_x);
			break;
		default:
			break;
		}
	}
}

// Changes player animation every 'X' seconds
void Sprite::animationCounter()
{
	double current_time_move_player = GetTickCount() - start_time_player_animation_;
	if (current_time_move_player >= player_animation_speed_)
	{
		if (animation_position_ == 0)
			animation_position_ = 1;
		else
			animation_position_ = 0;
		start_time_player_animation_ = GetTickCount();
	}
}