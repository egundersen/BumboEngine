#include "NPCSprite.h"
#include <iostream>

NPCSprite::NPCSprite(int sprite_width, int sprite_height, std::vector<std::vector<std::string>> &matrix_display, std::vector<std::vector<char>>& world_matrix)
	: Sprite(sprite_width, sprite_height, matrix_display), world_matrix_{ world_matrix }
{

}

// Draws character sprites on matrix
void NPCSprite::initializeSprites(std::vector<Image*> sprite_states)
{
	addImageToMatrix(sprite_width_ / 2 - 1, sprite_height_ / 2 - 1, *sprite_states[0], up_1_);
	addImageToMatrix(sprite_width_ / 2 - 1, sprite_height_ / 2 - 1, *sprite_states[1], down_1_);
	addImageToMatrix(sprite_width_ / 2 - 1, sprite_height_ / 2 - 1, *sprite_states[2], left_1_);
	addImageToMatrix(sprite_width_ / 2 - 1, sprite_height_ / 2 - 1, *sprite_states[3], right_1_);
	addImageToMatrix(sprite_width_ / 2 - 1, sprite_height_ / 2 - 1, *sprite_states[4], up_2_);
	addImageToMatrix(sprite_width_ / 2 - 1, sprite_height_ / 2 - 1, *sprite_states[5], down_2_);
	addImageToMatrix(sprite_width_ / 2 - 1, sprite_height_ / 2 - 1, *sprite_states[6], left_2_);
	addImageToMatrix(sprite_width_ / 2 - 1, sprite_height_ / 2 - 1, *sprite_states[7], right_2_);
	addImageToMatrix(sprite_width_ / 2 - 1, sprite_height_ / 2 - 1, *sprite_states[8], up_s_);
	addImageToMatrix(sprite_width_ / 2 - 1, sprite_height_ / 2 - 1, *sprite_states[9], down_s_);
	addImageToMatrix(sprite_width_ / 2 - 1, sprite_height_ / 2 - 1, *sprite_states[10], left_s_);
	addImageToMatrix(sprite_width_ / 2 - 1, sprite_height_ / 2 - 1, *sprite_states[11], right_s_);
}

// Replaces sprite with blank spaces on the world matrix
void NPCSprite::removeSprite(int center_position_x, int center_position_y)
{
	for (int i = 0; i < sprite_height_; i++)
		for (int j = 0; j < sprite_width_; j++)
			world_matrix_[center_position_y + i][center_position_x + j] = ' ';
}

// Displays given sprite to the world matrix
void NPCSprite::displaySpriteAtDirection(std::vector<std::vector<char>>& direction, int center_position_y, int center_position_x)
{
	for (int i = 0; i < sprite_height_; i++)
		for (int j = 0; j < sprite_width_; j++)
			//if (direction[i][j] != ' ')
			world_matrix_[center_position_y + i][center_position_x + j] = direction[i][j];
}
