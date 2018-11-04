#include "MatrixBase.h"
#include "AttackPatternBase.h"
#include "Attacks.h"

#ifndef ATTACKPATTERN_SHOOTHORIZONTAL_H
#define ATTACKPATTERN_SHOOTHORIZONTAL_H

class AttackPattern_ShootHorizontal : public AttackPatternBase
{
public:
	AttackPattern_ShootHorizontal(int width, int height, std::vector<std::vector<std::string>> &matrix_display, int player_health, int number_of_attacks);

	// Setters
	void OnBeginAttack(int player_health);
	void refreshScreen();
	void createAttack(int reverse_direction,int min_position_x, int max_position_x, int trail_length, int height_y, int speed);
};

#endif // !ATTACKPATTERN_SHOOTHORIZONTAL_H
