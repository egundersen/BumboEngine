#include "MatrixBase.h"
#include "AttackBase.h"

#ifndef ATTACK_EXPLODE_H
#define ATTACK_EXPLODE_H

class Attack_Explode : public AttackBase, MatrixBase
{
public:
	explicit Attack_Explode(int width, int height, PlayerPosition &player_position, std::vector<std::vector<char>> &matrix, bool **&element_is_occupied, int center_position_x, int center_position_y, int diameter, int delay, int duration_of_explosion);
	~Attack_Explode();

	// Setters
	void move();

private:
	// Setters
	void detectCollision();

	int center_position_x_, center_position_y_, start_time_update_attack_, diameter_, delay_, duration_of_explosion_;
};

#endif // !ATTACK_EXPLODE_H
