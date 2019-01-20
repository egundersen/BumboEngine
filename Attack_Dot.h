#ifndef ATTACK_LINE_H
#define ATTACK_LINE_H

#include "AttackBase.h"

class Attack_Dot : public AttackBase
{
public:
	explicit Attack_Dot(int width, int height, PlayerPosition &player_position, Matrix &attack_matrix, bool **&element_is_occupied,
		int position_2D, int speed, char direction, int slip_modifier, char slip_direction);
	virtual ~Attack_Dot();

	// Setters
	virtual void move();

protected:
	virtual void detectCollision();
	int position_, position_2D_, ending_position_, speed_, slip_modifier_, slip_;
	char direction_, slip_direction_;
};

#endif // !ATTACK_LINE_H
