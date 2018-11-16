#include "MatrixBase.h"
#include "AttackBase.h"

#ifndef ATTACK_VERTICLEGAP_H
#define ATTACK_VERTICLEGAP_H

class Attack_VerticleGap : public AttackBase, MatrixBase
{
public:
	explicit Attack_VerticleGap(int width, int height, PlayerPosition &player_position, std::vector<std::vector<char>> &matrix, bool **&element_is_occupied, int gap_position_x, int position_y, int gap_width, int screen_duration, int move_delay);
	~Attack_VerticleGap();

	// Setters
	void move();

private:
	// Setters
	void detectCollision();

	bool reverse_;
	int gap_position_x_, position_y_, start_time_update_attack_, gap_width_, screen_duration_, start_time_finish_attack_, move_delay_;
};

#endif // !ATTACK_VERTICLEGAP_H
