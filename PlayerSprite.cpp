#include "PlayerSprite.h"
#include <Windows.h>

PlayerSprite::PlayerSprite(int sprite_width, int sprite_height, std::vector<std::vector<std::string>> &matrix_display)
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
	initializeSprites();
	start_time_player_animation_ = GetTickCount();
}

// Chooses what to display to the screen
void PlayerSprite::displayPlayer(int screen_width, int screen_height)
{
	if (!is_moving_vertically_ && !is_moving_horizontally)
	{
		switch (direction_)
		{
		case 'u':
			displaySpriteAtDirection(up_s_, screen_height, screen_width);
			break;
		case 'd':
			displaySpriteAtDirection(down_s_, screen_height, screen_width);
			break;
		case 'l':
			displaySpriteAtDirection(left_s_, screen_height, screen_width);
			break;
		case 'r':
			displaySpriteAtDirection(right_s_, screen_height, screen_width);
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
			displaySpriteAtDirection(up_1_, screen_height, screen_width);
			break;
		case 'd':
			displaySpriteAtDirection(down_1_, screen_height, screen_width);
			break;
		case 'l':
			displaySpriteAtDirection(left_1_, screen_height, screen_width);
			break;
		case 'r':
			displaySpriteAtDirection(right_1_, screen_height, screen_width);
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
			displaySpriteAtDirection(up_2_, screen_height, screen_width);
			break;
		case 'd':
			displaySpriteAtDirection(down_2_, screen_height, screen_width);
			break;
		case 'l':
			displaySpriteAtDirection(left_2_, screen_height, screen_width);
			break;
		case 'r':
			displaySpriteAtDirection(right_2_, screen_height, screen_width);
			break;
		default:
			break;
		}
	}

	animationCounter();
}

// Decide whether player should use "moving" animation
void PlayerSprite::setPlayerMoving(std::string direction)
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
void PlayerSprite::animationCounter()
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

// Draws character sprites on matrix
void PlayerSprite::initializeSprites()
{
	Image up_1("   @@@@   Z  XXX@@X  Z   XXXX   Z OXXXXXXO ZO XXXXXXO Z  XU  UX  Z");
	Image down_1("   @@@@   Z  X[][]X  Z   XXXX   Z OXXXXXXO ZO XXXXXXO Z  XU  UX  Z");
	Image right_1("   @@@@   Z  @@X[]X  Z   @XXX  OZ  OXXXXXO Z  XXXXXX  Z  XU   XX Z");
	Image left_1("   @@@@   Z  X[]X@@  ZO  XXX@   Z OXXXXXO  Z  XXXXXX  Z XX   UX  Z");
	Image up_2("   @@@@   Z  XXX@@X  Z   XXXX   Z OXXXXXXO Z OXXXXXX OZ  XU  UX  Z");
	Image down_2("   @@@@   Z  X[][]X  Z   XXXX   Z OXXXXXXO Z OXXXXXX OZ  XU  UX  Z");
	Image right_2("   @@@@   Z  @@X[]X  Z   @XXX  OZ  OXXXXXO Z XXXXXXX  Z U=  XU   Z");
	Image left_2("   @@@@   Z  X[]X@@  ZO  XXX@   Z OXXXXXO  Z  XXXXXXX Z   UX  =U Z");
	Image up_s("   @@@@   Z  XXX@@X  Z   XXXX   Z OXXXXXXO Z OXXXXXXO Z  XU  UX  Z");
	Image down_s("   @@@@   Z  X[][]X  Z   XXXX   Z OXXXXXXO Z OXXXXXXO Z  XU  UX  Z");
	Image right_s("   @@@@   Z  @@X[]X  Z   @XXX   Z  OXXXXO  Z  XXXXXXO Z  XU  UX  Z");
	Image left_s("   @@@@   Z  X[]X@@  Z   XXX@   Z  OXXXXO  Z OXXXXXX  Z  XU  UX  Z");

	addImageToMatrix(sprite_width_ / 2 - 1, sprite_height_ / 2 - 1, up_1, up_1_);
	addImageToMatrix(sprite_width_ / 2 - 1, sprite_height_ / 2 - 1, down_1, down_1_);
	addImageToMatrix(sprite_width_ / 2 - 1, sprite_height_ / 2 - 1, left_1, left_1_);
	addImageToMatrix(sprite_width_ / 2 - 1, sprite_height_ / 2 - 1, right_1, right_1_);
	addImageToMatrix(sprite_width_ / 2 - 1, sprite_height_ / 2 - 1, up_2, up_2_);
	addImageToMatrix(sprite_width_ / 2 - 1, sprite_height_ / 2 - 1, down_2, down_2_);
	addImageToMatrix(sprite_width_ / 2 - 1, sprite_height_ / 2 - 1, left_2, left_2_);
	addImageToMatrix(sprite_width_ / 2 - 1, sprite_height_ / 2 - 1, right_2, right_2_);
	addImageToMatrix(sprite_width_ / 2 - 1, sprite_height_ / 2 - 1, up_s, up_s_);
	addImageToMatrix(sprite_width_ / 2 - 1, sprite_height_ / 2 - 1, down_s, down_s_);
	addImageToMatrix(sprite_width_ / 2 - 1, sprite_height_ / 2 - 1, left_s, left_s_);
	addImageToMatrix(sprite_width_ / 2 - 1, sprite_height_ / 2 - 1, right_s, right_s_);
}

// Displays given sprite to the screen
void PlayerSprite::displaySpriteAtDirection(std::vector<std::vector<char>> &direction, int screen_height, int screen_width)
{
	for (int i = 0; i < sprite_height_; i++)
		for (int j = 0; j < sprite_width_; j++)
			if (direction[i][j] != ' ')
				matrix_display_[i + screen_height / 2 - 3][j + screen_width / 2 - 5] = std::string(1, direction[i][j]);
}
