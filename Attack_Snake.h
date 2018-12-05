#include "MatrixBase.h"
#include "AttackBase.h"

#ifndef ATTACK_SNAKE_H
#define ATTACK_SNAKE_H

class Attack_Snake : public AttackBase, MatrixBase
{
public:
	explicit Attack_Snake(int width, int height, PlayerPosition &player_position, std::vector<std::vector<char>> &matrix, bool **&element_is_occupied, int head_position_x, int head_position_y, int duration_of_attack, int speed);
	~Attack_Snake();

	// Setters
	void move();

private:
	// Setters
	void detectCollision();

	int head_position_x_, head_position_y_, start_time_end_attack_, duration_of_attack_, speed_;
};

#endif // !ATTACK_SNAKE_H