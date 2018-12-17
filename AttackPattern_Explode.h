#include "MatrixBase.h"
#include "AttackPatternBase.h"
#include "Attacks.h"

#ifndef ATTACKPATTERN_EXPLODE_H
#define ATTACKPATTERN_EXPLODE_H

class AttackPattern_Explode : public AttackPatternBase
{
public:
	explicit AttackPattern_Explode(int width, int height, Matrix &screen_matrix, int &player_health, int number_of_attacks);
	virtual ~AttackPattern_Explode() {}

	// Setters
	void OnBeginAttack();
	void refreshScreen();
	void createAttack(int center_position_x, int center_position_y);
protected:
	// Setters
	virtual void setAttackParameters() {}

	int create_attack_delay_, attack_diameter_, delay_till_explode_, duration_of_explosion_;
};

class Explode_Fast : public AttackPattern_Explode
{
public:
	using AttackPattern_Explode::AttackPattern_Explode;

private:
	void setAttackParameters()
	{
		create_attack_delay_ = 2;
		attack_diameter_ = 4;
		delay_till_explode_ = 1000;
		duration_of_explosion_ = 1500;
	}
};

class Explode_Slow : public AttackPattern_Explode
{
public:
	using AttackPattern_Explode::AttackPattern_Explode;

private:
	void setAttackParameters()
	{
		create_attack_delay_ = 75;
		attack_diameter_ = 8;
		delay_till_explode_ = 2000;
		duration_of_explosion_ = 1000;
	}
};

class Explode_Slowest : public AttackPattern_Explode
{
public:
	using AttackPattern_Explode::AttackPattern_Explode;

private:
	void setAttackParameters()
	{
		create_attack_delay_ = 500;
		attack_diameter_ = 16;
		delay_till_explode_ = 1000;
		duration_of_explosion_ = 2000;
	}
};
#endif // !ATTACKPATTERN_EXPLODE_H
