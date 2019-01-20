#ifndef ATTACKPATTERN_COORDINATEDSTORM_H
#define ATTACKPATTERN_COORDINATEDSTORM_H

#include "AttackPatternBase.h"

class AttackPattern_CoordinatedStorm : public AttackPatternBase
{
public:
	AttackPattern_CoordinatedStorm(int width, int height, Matrix &screen_matrix, PlayerDefinition &player, int number_of_attacks, int creation_speed, int movement_speed, char direction, int slip_modifier, char slip_direction, bool dynamic_movement_speed, bool dynamic_creation_speed, int swap_modifier_speed);

	// Setters
	void OnBeginAttack();
	void refreshScreen();
	void createAttack(int reverse_direction, int position_2D_, int speed);
private:
	char direction_, slip_direction_;
	int slip_modifier_, max_starting_position_, creation_speed_, movement_speed_,
		start_time_modify_speed_, initial_movement_speed_, initial_creation_speed_, swap_modifier_speed_;
	bool dynamic_movement_speed_, dynamic_creation_speed_;
};

#endif // !ATTACKPATTERN_COORDINATEDSTORM_H
