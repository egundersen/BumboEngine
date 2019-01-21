#ifndef ATTACKPATTERN_SNAKEEXPLODE_H
#define ATTACKPATTERN_SNAKEEXPLODE_H

#include "AttackPatternBase.h"

class AttackPattern_SnakeExplode : public AttackPatternBase
{
public:
	explicit AttackPattern_SnakeExplode(int width, int height, Matrix &screen_matrix, PlayerDefinition &player, int number_of_explosions, int duration_of_attack, int snake_speed);
	virtual ~AttackPattern_SnakeExplode() {}

	// Setters
	void OnBeginAttack();
	void refreshScreen();
	void createAttack1(int head_position_x, int head_position_y, int duration_of_attack, int speed);
	void createAttack2(int center_position_x, int center_position_y);
protected:
	// Setters
	virtual void setAttackParameters() {}

	int create_attack_delay_, attack_diameter_, delay_till_explode_, duration_of_explosion_;
private:
	int duration_of_attack_, snake_speed_;
};

class SnakeExplode_Fast : public AttackPattern_SnakeExplode
{
public:
	using AttackPattern_SnakeExplode::AttackPattern_SnakeExplode;

private:
	void setAttackParameters()
	{
		create_attack_delay_ = 2;
		attack_diameter_ = 4;
		delay_till_explode_ = 1000;
		duration_of_explosion_ = 1500;
	}
};
class SnakeExplode_Slow : public AttackPattern_SnakeExplode
{
public:
	using AttackPattern_SnakeExplode::AttackPattern_SnakeExplode;

private:
	void setAttackParameters()
	{
		create_attack_delay_ = 75;
		attack_diameter_ = 8;
		delay_till_explode_ = 2000;
		duration_of_explosion_ = 1000;
	}
};

class SnakeExplode_Slowest : public AttackPattern_SnakeExplode
{
public:
	using AttackPattern_SnakeExplode::AttackPattern_SnakeExplode;

private:
	void setAttackParameters()
	{
		create_attack_delay_ = 500;
		attack_diameter_ = 16;
		delay_till_explode_ = 1000;
		duration_of_explosion_ = 2000;
	}
};
class SnakeExplode_Mine : public AttackPattern_SnakeExplode
{
public:
	using AttackPattern_SnakeExplode::AttackPattern_SnakeExplode;

private:
	void setAttackParameters()
	{
		create_attack_delay_ = 100;
		attack_diameter_ = 6;
		delay_till_explode_ = 2000;
		duration_of_explosion_ = 15000;
	}
};

#endif // !ATTACKPATTERN_SNAKEEXPLODE_H