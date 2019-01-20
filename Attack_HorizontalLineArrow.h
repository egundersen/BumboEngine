#ifndef ATTACK_HORIZONTALLINEARROW_H
#define ATTACK_HORIZONTALLINEARROW_H

#include "AttackBase.h"

class Attack_HorizontalLineArrow : public AttackBase
{
public:
	explicit Attack_HorizontalLineArrow(int width, int height, PlayerPosition &player_position, Matrix &attack_matrix, bool **&element_is_occupied,int min_position_x, int max_position_x, int trail_length, int height_y, int speed);
	virtual ~Attack_HorizontalLineArrow();

	// Setters
	virtual void move() {};

protected:
	virtual void detectCollision();
	int min_position_x_, max_position_x_, trail_speed_, trail_length_, height_y_, speed_;
};

class HorizontalLineArrow_Right : public Attack_HorizontalLineArrow
{
public:
	using Attack_HorizontalLineArrow::Attack_HorizontalLineArrow;

	// Setters
	void move();
};

class HorizontalLineArrow_Left : public Attack_HorizontalLineArrow
{
public:
	using Attack_HorizontalLineArrow::Attack_HorizontalLineArrow;

	// Setters
	void move();
};

#endif // !ATTACK_HORIZONTALLINEARROW_H
