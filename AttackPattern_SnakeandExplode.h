#include "MatrixBase.h"
#include "AttackPatternBase.h"
#include "Attacks.h"

#ifndef ATTACKPATTERN_SNAKEANDEXPLODE_H
#define ATTACKPATTERN_SNAKEANDEXPLODE_H

class AttackPattern_SnakeandExplode : public AttackPatternBase
{
public:
	explicit AttackPattern_SnakeandExplode(int width, int height, std::vector<std::vector<std::string>> &matrix_display, int &player_health, int number_of_attacks);
	virtual ~AttackPattern_SnakeandExplode() {}

	// Setters
	void OnBeginAttack();
	void refreshScreen();
	void createAttack1(int head_position_x, int head_position_y, int duration_of_attack, int speed);
	void createAttack2(int center_position_x, int center_position_y);
protected:
	// Setters
	virtual void setAttackParameters() {}

	int create_attack_delay_, attack_diameter_, delay_till_explode_, duration_of_explosion_;
};

class SnakeandExplode_Fast : public AttackPattern_SnakeandExplode
{
public:
	using AttackPattern_SnakeandExplode::AttackPattern_SnakeandExplode;

private:
	void setAttackParameters()
	{
		create_attack_delay_ = 2;
		attack_diameter_ = 4;
		delay_till_explode_ = 1000;
		duration_of_explosion_ = 1500;
	}
};
class SnakeandExplode_Slow : public AttackPattern_SnakeandExplode
{
public:
	using AttackPattern_SnakeandExplode::AttackPattern_SnakeandExplode;

private:
	void setAttackParameters()
	{
		create_attack_delay_ = 75;
		attack_diameter_ = 8;
		delay_till_explode_ = 2000;
		duration_of_explosion_ = 1000;
	}
};

class SnakeandExplode_Slowest : public AttackPattern_SnakeandExplode
{
public:
	using AttackPattern_SnakeandExplode::AttackPattern_SnakeandExplode;

private:
	void setAttackParameters()
	{
		create_attack_delay_ = 500;
		attack_diameter_ = 16;
		delay_till_explode_ = 1000;
		duration_of_explosion_ = 2000;
	}
};
class SnakeandExplode_Mine : public AttackPattern_SnakeandExplode
{
public:
	using AttackPattern_SnakeandExplode::AttackPattern_SnakeandExplode;

private:
	void setAttackParameters()
	{
		create_attack_delay_ = 100;
		attack_diameter_ = 6;
		delay_till_explode_ = 2000;
		duration_of_explosion_ = 15000;
	}
};

#endif // !ATTACKPATTERN_SNAKEANDEXPLODE_H