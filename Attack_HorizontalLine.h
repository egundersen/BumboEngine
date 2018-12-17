#include "MatrixBase.h"
#include "AttackBase.h"

#ifndef ATTACK_HORIZONTALLINE_H
#define ATTACK_HORIZONTALLINE_H

class Attack_HorizontalLine : public AttackBase
{
public:
	explicit Attack_HorizontalLine(int width, int height, PlayerPosition &player_position, Matrix &attack_matrix, bool **&element_is_occupied,int min_position_x, int max_position_x, int trail_length, int height_y, int speed);
	virtual ~Attack_HorizontalLine();

	// Setters
	virtual void move() {};

protected:
	virtual void detectCollision();
	int min_position_x_, max_position_x_, trail_speed_, trail_length_, height_y_, speed_;
};

class HorizontalLine_Right : public Attack_HorizontalLine
{
public:
	using Attack_HorizontalLine::Attack_HorizontalLine;

	// Setters
	void move();
};

class HorizontalLine_Left : public Attack_HorizontalLine
{
public:
	using Attack_HorizontalLine::Attack_HorizontalLine;

	// Setters
	void move();
};

#endif // !ATTACK_HORIZONTALLINE_H
