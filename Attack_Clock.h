#ifndef ATTACK_CLOCK_H
#define ATTACK_CLOCK_H

#include "AttackBase.h"

class Attack_Clock : public AttackBase, MatrixBase
{
public:
	explicit Attack_Clock(int width, int height, PlayerPosition &player_position, Matrix &attack_matrix, bool **&element_is_occupied, int center_position_x, int center_position_y, int diameter, int angle);
	~Attack_Clock();

	// Setters
	void move();

private:
	// Setters
	void detectCollision();

	int center_position_x_, center_position_y_, start_time_update_attack_, diameter_, angle_;
};

#endif // !ATTACK_CLOCK_H
