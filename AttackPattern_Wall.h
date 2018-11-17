#include "MatrixBase.h"
#include "AttackPatternBase.h"
#include "Attacks.h"

#ifndef ATTACKPATTERN_WALL_H
#define ATTACKPATTERN_WALL_H

class AttackPattern_Wall : public AttackPatternBase
{
public:
	AttackPattern_Wall(int width, int height, std::vector<std::vector<std::string>> &matrix_display, int &player_health, int number_of_attacks);

	// Setters
	void OnBeginAttack();
	void refreshScreen();
	void createAttack( int min_position_x, int max_position_x, int gap_height,int speed);
};

#endif // !ATTACKPATTERN_WALL_H
