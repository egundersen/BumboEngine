#ifndef ATTACKPATTERN_SAFESQUARES_H
#define ATTACKPATTERN_SAFESQUARES_H

#include "AttackPatternBase.h"

class AttackPattern_SafeSquares : public AttackPatternBase
{
public:
	explicit AttackPattern_SafeSquares(int width, int height, Matrix &screen_matrix, PlayerDefinition &player, int number_of_attacks);
	virtual ~AttackPattern_SafeSquares() {}

	// Setters
	void OnBeginAttack();
	void refreshScreen();
	void createAttack(int center_position_x, int center_position_y);
protected:
	// Setters
	virtual void setAttackParameters() {}

	int create_attack_delay_, attack_diameter_, delay_till_explode_, duration_of_explosion_;
};

class SafeSquares_Fast_Easy : public AttackPattern_SafeSquares
{
public:
	using AttackPattern_SafeSquares::AttackPattern_SafeSquares;

private:
	void setAttackParameters()
	{
		create_attack_delay_ = 3400;
		attack_diameter_ = 30;
		delay_till_explode_ = 1800;
		duration_of_explosion_ = 1500;
	}
};

class SafeSquares_Fast : public AttackPattern_SafeSquares
{
public:
	using AttackPattern_SafeSquares::AttackPattern_SafeSquares;

private:
	void setAttackParameters()
	{
		create_attack_delay_ = 2800;
		attack_diameter_ = 26;
		delay_till_explode_ = 1200;
		duration_of_explosion_ = 1500;
	}
};

class SafeSquares_Slow : public AttackPattern_SafeSquares
{
public:
	using AttackPattern_SafeSquares::AttackPattern_SafeSquares;

private:
	void setAttackParameters()
	{
		create_attack_delay_ = 3600;
		attack_diameter_ = 14;
		delay_till_explode_ = 2000;
		duration_of_explosion_ = 1500;
	}
};

class SafeSquares_Slowest : public AttackPattern_SafeSquares
{
public:
	using AttackPattern_SafeSquares::AttackPattern_SafeSquares;

private:
	void setAttackParameters()
	{
		create_attack_delay_ = 4200;
		attack_diameter_ = 2;
		delay_till_explode_ = 2500;
		duration_of_explosion_ = 1500;
	}
};
#endif // !ATTACKPATTERN_SAFESQUARES_H
