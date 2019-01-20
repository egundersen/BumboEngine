#ifndef ATTACKPATTERN_SHOOTANDSNAKE_H
#define ATTACKPATTERN_SHOOTANDSNAKE_H

#include "AttackPatternBase.h"

class AttackPattern_ShootandSnake : public AttackPatternBase
{
public:
	AttackPattern_ShootandSnake(int width, int height, Matrix &screen_matrix, PlayerDefinition &player, int number_of_attacks);

	// Setters
	void OnBeginAttack();
	void refreshScreen();
	void createAttack1(int reverse_direction, int min_position_x, int max_position_x, int trail_length, int height_y, int speed);
	void createAttack2(int head_position_x, int head_position_y, int duration_of_attack, int speed);
};

#endif // !ATTACKPATTERN_SHOOTHORIZONTAL_H