#include "PlayerSprite.h"

// Draws character sprites on matrix
void PlayerSprite::initializeSprites()
{
	// moving
	Image up_1("   @@@@   Z  XXX@@X  Z   XXXX   Z O#XXXX#O ZO ######O Z  %U  U%  Z");
	Image down_1("   @@@@   Z  X[][]X  Z   XXXX   Z O#XXXX#O ZO ######O Z  %U  U%  Z");
	Image right_1("   @@@@   Z  @@X[]X  Z   @XXX   Z  O#XX#O  Z  O%###%O Z   %%  %  Z");
	Image left_1("   @@@@   Z  X[]X@@  Z   XXX@   Z  O#XX#O  Z O%###%O  Z  %  %%   Z");
	Image up_2("   @@@@   Z  XXX@@X  Z   XXXX   Z O#XXXX#O Z O###### OZ  %U  U%  Z");
	Image down_2("   @@@@   Z  X[][]X  Z   XXXX   Z O#XXXX#O Z O###### OZ  %U  U%  Z");
	Image right_2("   @@@@   Z  @@X[]X  Z   @XXX O Z  O#XX#O  Z %%O#%#   Z %=  %%   Z");
	Image left_2("   @@@@   Z  X[]X@@  Z O XXX@   Z  O#XX#O  Z   #%#O%% Z   %%  =% Z");

	// Not moving
	Image up_s("   @@@@   Z  XXX@@X  Z   XXXX   Z O#XXXX#O Z O######O Z  %U  U%  Z");
	Image down_s("   @@@@   Z  X[][]X  Z   XXXX   Z O#XXXX#O Z O######O Z  %U  U%  Z");
	Image right_s("   @@@@   Z  @@X[]X  Z   @XXX   Z  O#XX#O  Z  ######O Z  %U  U%  Z");
	Image left_s("   @@@@   Z  X[]X@@  Z   XXX@   Z  O#XX#O  Z O######  Z  %U  U%  Z");

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

// Displays given sprite to the screen
void PlayerSprite::displaySpriteAtDirection(Matrix& direction, int top_left_position_x, int top_left_position_y)
{
	for (int i = 0; i < sprite_height_; i++)
		for (int j = 0; j < sprite_width_; j++)
		{
			char temp = direction[i][j];
			if (temp != ' ')
				screen_matrix_[i + top_left_position_y / 2 - 3][j + top_left_position_x / 2 - 5] = temp;
		}
}
