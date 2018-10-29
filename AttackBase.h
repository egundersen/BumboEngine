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
	virtual bool hasHitPlayer() { return has_hit_player_; }
	virtual bool hasAttackFinished() { return has_attack_finished_; }
	virtual int getInt() { return 5; }
protected:
	int width_;
	int height_;
	PlayerPosition &player_position_;
	bool has_hit_player_;
	bool has_attack_finished_;
	std::vector<std::vector<char>> &matrix_;
	bool **&element_is_occupied_;
};

#endif // !ATTACKBASE_H
