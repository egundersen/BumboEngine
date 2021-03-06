#ifndef ATTACKPATTERN_SHOOTATPLAYER_H
#define ATTACKPATTERN_SHOOTATPLAYER_H

#include "AttackPatternBase.h"

class AttackPattern_ShootAtPlayer : public AttackPatternBase
{
public:
	AttackPattern_ShootAtPlayer(int width, int height, Matrix &screen_matrix, PlayerDefinition &player, int number_of_attacks);

	// Setters
	void OnBeginAttack();
	void refreshScreen();
	void createAttack(int reverse_direction, int min_position_x, int max_position_x, int trail_length, int height_y, int speed);
};

#endif // !ATTACKPATTERN_SHOOTATPLAYER_H
