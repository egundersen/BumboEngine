#ifndef ATTACKPATTERN_HAILSTORM_H
#define ATTACKPATTERN_HAILSTORM_H

#include "AttackPatternBase.h"

class HailStorm : public AttackPatternBase
{
public:
	HailStorm(int width, int height, Matrix &screen_matrix, PlayerDefinition &player, int number_of_attacks, char direction, int slip_modifier, char slip_direction);

	// Setters
	void OnBeginAttack();
	void refreshScreen();
	void createAttack(int reverse_direction, int position_2D_, int speed);
private:
	char direction_, slip_direction_;
	int slip_modifier_, max_starting_position_;
};

#endif // !ATTACKPATTERN_HAILSTORM_H