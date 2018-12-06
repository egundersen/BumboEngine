#include "MatrixBase.h"
#include "AttackPatternBase.h"
#include "Attacks.h"

#ifndef ATTACKPATTERN_SHOOTANDEXPLODE_H
#define ATTACKPATTERN_SHOOTANDEXPLODE_H

class AttackPattern_ShootandExplode : public AttackPatternBase
{
public:
	explicit AttackPattern_ShootandExplode(int width, int height, std::vector<std::vector<std::string>> &matrix_display, int &player_health, int number_of_attacks);
	virtual ~AttackPattern_ShootandExplode() {}

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

class ShootandExplode_Fast : public AttackPattern_ShootandExplode
{
public:
	using AttackPattern_ShootandExplode::AttackPattern_ShootandExplode;

private:
	void setAttackParameters()
	{
		create_attack_delay_ = 2;
		attack_diameter_ = 4;
		delay_till_explode_ = 1000;
		duration_of_explosion_ = 1500;
	}
};
class ShootandExplode_Slow : public AttackPattern_ShootandExplode
{
public:
	using AttackPattern_ShootandExplode::AttackPattern_ShootandExplode;

private:
	void setAttackParameters()
	{
		create_attack_delay_ = 75;
		attack_diameter_ = 8;
		delay_till_explode_ = 2000;
		duration_of_explosion_ = 1000;
	}
};

class ShootandExplode_Slowest : public AttackPattern_ShootandExplode
{
public:
	using AttackPattern_ShootandExplode::AttackPattern_ShootandExplode;

private:
	void setAttackParameters()
	{
		create_attack_delay_ = 500;
		attack_diameter_ = 16;
		delay_till_explode_ = 1000;
		duration_of_explosion_ = 2000;
	}
};

#endif // !ATTACKPATTERN_SHOOTANDEXPLODE_H