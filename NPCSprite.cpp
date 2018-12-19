#include "NPCSprite.h"
#include <tuple>
#include <iostream>

NPCSprite::NPCSprite(int sprite_width, int sprite_height, Matrix &screen_matrix, Matrix &world_matrix)
	: Sprite(sprite_width, sprite_height, screen_matrix), world_matrix_{ world_matrix }
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

// Erases sprite and square around sprite from world matrix
void NPCSprite::DEBUG_eraseSquareSurroundingSprite(int top_left_position_x, int top_left_position_y)
{
	for (int i = 0; i < sprite_height_ - 2; i++)
		for (int j = 0; j < sprite_width_ - 2; j++)
				world_matrix_[top_left_position_y + i][top_left_position_x + j] = ' ';
}

// Displays given sprite to the world matrix
void NPCSprite::displaySpriteAtDirection(Matrix& direction, int top_left_position_x, int top_left_position_y)
{
	for (int i = 0; i < sprite_height_; i++)
		for (int j = 0; j < sprite_width_; j++)
		{
			char temp = direction[i][j];
			if (temp != ' ')
			{
				world_matrix_[top_left_position_y + i][top_left_position_x + j] = temp;
				world_matrix_[top_left_position_y + i][top_left_position_x + j].setColor(direction[i][j].getRGBA());
			}
		}
}

// Displays a fake, "GHOST" of the sprite (does not actually move them) on the Matrix Display
void NPCSprite::displayGhostSpriteAtDirection(Matrix& direction, int top_left_position_x, int top_left_position_y, int screen_width_, int screen_height_, char moving_direction)
{
	for (int i = 0; i < sprite_height_; i++)
		for (int j = 0; j < sprite_width_; j++) // TODO: These may have been copied incorrectly...
		{
			char temp = direction[i][j];
			switch (moving_direction)
			{
			case 'd':
				if (direction[i][j] != ' ' && top_left_position_y < screen_height_ - sprite_height_ / 2 - 1)
				{
					screen_matrix_[top_left_position_y + i][top_left_position_x + j] = temp;
					screen_matrix_[top_left_position_y + i][top_left_position_x + j].setColor(direction[i][j].getRGBA());
				}
				break;
			case 'u':
				if (direction[i][j] != ' ' && top_left_position_y > sprite_height_ / 2 - 1)
				{
					screen_matrix_[top_left_position_y + i][top_left_position_x + j] = temp;
					screen_matrix_[top_left_position_y + i][top_left_position_x + j].setColor(direction[i][j].getRGBA());
				}
			case 'r':
				if (direction[i][j] != ' ' && top_left_position_x < screen_width_ - sprite_width_ / 2 - 1)
				{
					screen_matrix_[top_left_position_y + i][top_left_position_x + j] = temp;
					screen_matrix_[top_left_position_y + i][top_left_position_x + j].setColor(direction[i][j].getRGBA());
				}
				break;
			case 'l':
				if (direction[i][j] != ' ' && top_left_position_x > sprite_width_ / 2 - 1)
				{
					screen_matrix_[top_left_position_y + i][top_left_position_x + j] = temp;
					screen_matrix_[top_left_position_y + i][top_left_position_x + j].setColor(direction[i][j].getRGBA());
				}
				break;
			}
		}
}

// Erases the exact positions of the world map that previously contained a sprite
void NPCSprite::eraseSpriteAtDirection(Matrix& direction, int top_left_position_x, int top_left_position_y)
{
	for (int i = 0; i < sprite_height_; i++)
		for (int j = 0; j < sprite_width_; j++)
			if (direction[i][j] != ' ')
				world_matrix_[top_left_position_y + i][top_left_position_x + j] = ' ';
}