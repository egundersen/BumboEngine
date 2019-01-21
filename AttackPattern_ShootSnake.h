#ifndef ATTACKPATTERN_SHOOTSNAKE_H
#define ATTACKPATTERN_SHOOTSNAKE_H

#include "AttackPatternBase.h"

class AttackPattern_ShootSnake : public AttackPatternBase
{
public:
	AttackPattern_ShootSnake(int width, int height, Matrix &screen_matrix, PlayerDefinition &player, int number_of_shots, int duration_of_attack, int snake_speed);

	// Setters
	void OnBeginAttack();
	void refreshScreen();
	void createAttack1(int reverse_direction, int min_position_x, int max_position_x, int trail_length, int height_y, int speed);
	void createAttack2(int head_position_x, int head_position_y, int duration_of_attack, int speed);

private:
	int duration_of_attack_, snake_speed_;
};

#endif // !ATTACKPATTERN_SHOOTHORIZONTAL_H