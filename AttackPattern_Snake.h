#ifndef ATTACKPATTERN_SNAKE_H
#define ATTACKPATTERN_SNAKE_H

#include "AttackPatternBase.h"

class AttackPattern_Snake : public AttackPatternBase
{
public:
	explicit AttackPattern_Snake(int width, int height, Matrix &screen_matrix, PlayerDefinition &player, int number_of_attacks, int duration_of_attack, int snake_speed);
	virtual ~AttackPattern_Snake() {}

	// Setters
	void OnBeginAttack();
	void refreshScreen();
	void createAttack(int head_position_x, int head_position_y, int duration_of_attack, int speed);
private:
	int duration_of_attack_, snake_speed_;
};

#endif // !ATTACKPATTERN_SNAKE_H
