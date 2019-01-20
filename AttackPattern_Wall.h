#ifndef ATTACKPATTERN_WALL_H
#define ATTACKPATTERN_WALL_H

#include "AttackPatternBase.h"

class AttackPattern_Wall : public AttackPatternBase
{
public:
	AttackPattern_Wall(int width, int height, Matrix &screen_matrix, PlayerDefinition &player, int number_of_attacks, int gap_width, int speed);

	// Setters
	void OnBeginAttack();
	void refreshScreen();
	void createAttack( int min_position_x, int max_position_x, int gap_height);

private:
	int gap_width_, speed_;
};

#endif // !ATTACKPATTERN_WALL_H
