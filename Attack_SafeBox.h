#ifndef ATTACK_SAFEBOX_H
#define ATTACK_SAFEBOX_H

#include "AttackBase.h"

class Attack_SafeBox : public AttackBase, MatrixBase
{
public:
	explicit Attack_SafeBox(int width, int height, PlayerPosition &player_position, Matrix &attack_matrix, bool **&element_is_occupied, int center_position_x, int center_position_y, int diameter, int delay, int duration_of_explosion);
	~Attack_SafeBox();

	// Setters
	void move();
	void erasePlayerPosition();

private:
	// Setters
	void detectCollision();
	void screenWarning();
	void screenKill();
	void safeZone();

	bool complete_1_, complete_2_;
	int center_position_x_, center_position_y_, start_time_update_attack_, diameter_, delay_, duration_of_explosion_;
};

#endif // !ATTACK_SAFEBOX_H
