#include "MatrixBase.h"

#ifndef PLAYER_H
#define PLAYER_H

class PlayerSprite : public MatrixBase
{

public:
	PlayerSprite(int sprite_width, int sprite_height, std::vector<std::vector<std::string>> &matrix_display);

	void displayPlayer(char direction, int screen_width, int screen_height);
	void setPlayerMoving(std::string direction);
	int getXPosition() { return x_position_; }
	int getYPosition() { return y_position_; }
	int getWidth() { return sprite_width_; }
	int getHeight() { return sprite_height_; }
private:
	void animationCounter();
	void initializeSprites();
	void displaySpriteAtDirection(std::vector<std::vector<char>> &direction, int screen_height, int screen_width);

	bool is_moving_vertically_, is_moving_horizontally;
	int sprite_width_, sprite_height_, animation_position_, start_time_player_animation_, x_position_,
		y_position_;
	std::vector<std::vector<std::string>> &matrix_display_;
	std::vector<std::vector<char>> up_1_, up_2_, up_s_, down_1_, down_2_, down_s_, right_1_, right_2_,
		right_s_, left_1_, left_2_, left_s_;
};

#endif // !PLAYER_H
