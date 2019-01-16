#include "AttackBase.h"

#ifndef ATTACK_LINE_H
#define ATTACK_LINE_H

class Attack_Line : public AttackBase
{
public:
	explicit Attack_Line(int width, int height, PlayerPosition &player_position, Matrix &attack_matrix, bool **&element_is_occupied,
		int min_position, int max_position, int position_2D, int trail_length, int speed, char approach_angle, char direction,
		int slip_2D, char slip_direction, int percentage_solid);
	virtual ~Attack_Line();

	// Setters
	virtual void move();

protected:
	virtual void detectCollision();
	int min_position_, max_position_, position_2D_, trail_length_, speed_, slip_2D_,
		percentage_solid_;
	char approach_angle_, direction_, slip_direction_;
};

#endif // !ATTACK_LINE_H
