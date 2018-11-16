#include "MatrixBase.h"
#include "AttackBase.h"

#ifndef ATTACK_BORDER_H
#define ATTACK_BORDER_H

class Attack_Border : public AttackBase, MatrixBase
{
public:
	Attack_Border(int width, int height, PlayerPosition &player_position, std::vector<std::vector<char>> &matrix, bool **&element_is_occupied);
	~Attack_Border();

	// Setters
	void onBeginAttack();
	void detectCollision();

protected:

	bool has_initialized_;
};

#endif // !ATTACK_BORDER_H
