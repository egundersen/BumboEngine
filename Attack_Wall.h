#include "MatrixBase.h"
#include "AttackBase.h"

#ifndef ATTACK_WALL_H
#define ATTACK_WALL_H

class Attack_Wall : public AttackBase
{
public:
	explicit Attack_Wall(int width, int height, PlayerPosition &player_position, Matrix &attack_matrix, bool **&element_is_occupied, int min_position_x, int max_position_x, int gap_height, int gap_width, int speed);
	 ~Attack_Wall();

	// Setters
	void move();

	// Getters
	bool hasHitPlayer() { return has_hit_player_; }
	bool hasAttackFinished() { return has_attack_finished_; }
protected:
	virtual void detectCollision();
	int min_position_x_, max_position_x_, speed_, gap_height_, gap_width_;
};
#endif // !ATTACK_WALL_H
