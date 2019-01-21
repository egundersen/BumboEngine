#ifndef ATTACKPATTERN_SHOOTEXPLODE_H
#define ATTACKPATTERN_SHOOTEXPLODE_H

#include "AttackPatternBase.h"

class AttackPattern_ShootExplode : public AttackPatternBase
{
public:
	explicit AttackPattern_ShootExplode(int width, int height, Matrix &screen_matrix, PlayerDefinition &player, int number_of_attacks);
	virtual ~AttackPattern_ShootExplode() {}

	// Setters
	void OnBeginAttack();
	void refreshScreen();
	void createAttack1(int center_position_x, int center_position_y);
	void createAttack2(int reverse_direction, int min_position_x, int max_position_x, int trail_length, int height_y, int speed);
protected:
	// Setters
	virtual void setAttackParameters() {}

	int create_attack_delay_, attack_diameter_, delay_till_explode_, duration_of_explosion_;
};

class ShootExplode_Fast : public AttackPattern_ShootExplode
{
public:
	using AttackPattern_ShootExplode::AttackPattern_ShootExplode;

private:
	void setAttackParameters()
	{
		create_attack_delay_ = 2;
		attack_diameter_ = 4;
		delay_till_explode_ = 1000;
		duration_of_explosion_ = 1500;
	}
};
class ShootExplode_Slow : public AttackPattern_ShootExplode
{
public:
	using AttackPattern_ShootExplode::AttackPattern_ShootExplode;

private:
	void setAttackParameters()
	{
		create_attack_delay_ = 75;
		attack_diameter_ = 8;
		delay_till_explode_ = 2000;
		duration_of_explosion_ = 1000;
	}
};

class ShootExplode_Slowest : public AttackPattern_ShootExplode
{
public:
	using AttackPattern_ShootExplode::AttackPattern_ShootExplode;

private:
	void setAttackParameters()
	{
		create_attack_delay_ = 500;
		attack_diameter_ = 16;
		delay_till_explode_ = 1000;
		duration_of_explosion_ = 2000;
	}
};

#endif // !ATTACKPATTERN_SHOOTEXPLODE_H