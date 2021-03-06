#ifndef SPRITE_H
#define SPRITE_H

#include "MatrixBase.h"

// Manages ASCII and the ability to move and change animations
class Sprite : public MatrixBase
{

public:
	explicit Sprite(int sprite_width, int sprite_height, Matrix &screen_matrix);
	virtual ~Sprite() {}

	// Setters
	virtual void displaySprite(int top_left_position_x, int top_left_position_y);
	void removeSprite(int top_left_position_x, int top_left_position_y);
	void displayGhostSprite(int top_left_position_x, int top_left_position_y, int screen_width, int screen_height, char moving_direction);
	void setPlayerAnimationSpeed(int player_animation_speed) { player_animation_speed_ = player_animation_speed; }
	void setDirection(char direction) { direction_ = direction; }
	void setMoving(std::string direction);
	virtual void initializeSprites() {}

	// Getters
	int getXPosition() { return x_position_; }
	int getYPosition() { return y_position_; }
	int getWidth() { return sprite_width_; }
	int getHeight() { return sprite_height_; }
	char getDirection() { return direction_; }
protected:
	// Setters
	void animationCounter();

	// Output Displays
	virtual void displaySpriteAtDirection(Matrix &direction, int top_left_position_x, int top_left_position_y) {}
	virtual void displayGhostSpriteAtDirection(Matrix &direction, int top_left_position_x, int top_left_position_y, int screen_width_, int screen_height_, char moving_direction) {}
	virtual void eraseSpriteAtDirection(Matrix &direction, int top_left_position_x, int top_left_position_y) {}

	bool is_moving_vertically_, is_moving_horizontally;
	char direction_;
	int sprite_width_, sprite_height_, animation_position_, start_time_player_animation_, x_position_,
		y_position_, player_animation_speed_;
	Matrix &screen_matrix_, up_1_, up_2_, up_s_, down_1_, down_2_, down_s_, right_1_, right_2_,
		right_s_, left_1_, left_2_, left_s_;
};

#endif // !SPRITE_H
