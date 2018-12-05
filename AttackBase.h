#include "MatrixBase.h"

#ifndef ATTACKBASE_H
#define ATTACKBASE_H

class AttackBase
{
public:
	explicit AttackBase(int width, int height, PlayerPosition &player_position, std::vector<std::vector<char>> &matrix, bool **&element_is_occupied);
	virtual ~AttackBase() {};

	// Setters
	virtual void move() {};

	// Getters
	bool hasHitPlayer() { return has_hit_player_; }
	bool hasAttackFinished() { return has_attack_finished_; }
protected:
	int width_, height_, start_time_update_attack_;
	bool has_hit_player_, has_attack_finished_, **&element_is_occupied_;
	PlayerPosition &player_position_;
	std::vector<std::vector<char>> &matrix_;
};

#endif // !ATTACKBASE_H
