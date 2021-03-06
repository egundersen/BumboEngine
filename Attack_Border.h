#ifndef ATTACK_BORDER_H
#define ATTACK_BORDER_H

#include "AttackBase.h"

class Attack_Border : public AttackBase, MatrixBase
{
public:
	Attack_Border(int width, int height, PlayerPosition &player_position, Matrix &attack_matrix, bool **&element_is_occupied);
	~Attack_Border();

	// Setters
	void onBeginAttack();
	void detectCollision();

protected:

	bool has_initialized_;
};

#endif // !ATTACK_BORDER_H
