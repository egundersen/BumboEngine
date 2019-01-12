#include "PlayerSprite.h"

// Draws character sprites on matrix
void PlayerSprite::initializeSprites(WorldSpriteContainer player_sprite)
{
	addImageToMatrix(sprite_width_ / 2 - 1, sprite_height_ / 2 - 1, *player_sprite.up_1, up_1_);
	addImageToMatrix(sprite_width_ / 2 - 1, sprite_height_ / 2 - 1, *player_sprite.down_1, down_1_);
	addImageToMatrix(sprite_width_ / 2 - 1, sprite_height_ / 2 - 1, *player_sprite.left_1, left_1_);
	addImageToMatrix(sprite_width_ / 2 - 1, sprite_height_ / 2 - 1, *player_sprite.right_1, right_1_);
	addImageToMatrix(sprite_width_ / 2 - 1, sprite_height_ / 2 - 1, *player_sprite.up_2, up_2_);
	addImageToMatrix(sprite_width_ / 2 - 1, sprite_height_ / 2 - 1, *player_sprite.down_2, down_2_);
	addImageToMatrix(sprite_width_ / 2 - 1, sprite_height_ / 2 - 1, *player_sprite.left_2, left_2_);
	addImageToMatrix(sprite_width_ / 2 - 1, sprite_height_ / 2 - 1, *player_sprite.right_2, right_2_);
	addImageToMatrix(sprite_width_ / 2 - 1, sprite_height_ / 2 - 1, *player_sprite.up_s, up_s_);
	addImageToMatrix(sprite_width_ / 2 - 1, sprite_height_ / 2 - 1, *player_sprite.down_s, down_s_);
	addImageToMatrix(sprite_width_ / 2 - 1, sprite_height_ / 2 - 1, *player_sprite.left_s, left_s_);
	addImageToMatrix(sprite_width_ / 2 - 1, sprite_height_ / 2 - 1, *player_sprite.right_s, right_s_);
}

// Displays given sprite to the screen
void PlayerSprite::displaySpriteAtDirection(Matrix& direction, int top_left_position_x, int top_left_position_y)
{
	for (int i = 0; i < sprite_height_; i++)
		for (int j = 0; j < sprite_width_; j++)
		{
			char temp = direction[i][j];
			if (temp != ' ')
			{
				screen_matrix_[i + top_left_position_y / 2 - 3][j + top_left_position_x / 2 - 5] = temp;
				screen_matrix_[i + top_left_position_y / 2 - 3][j + top_left_position_x / 2 - 5].setColor(direction[i][j].getRGBA());
			}
		}
}
