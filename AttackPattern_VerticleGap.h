#include "MatrixBase.h"
#include "AttackPatternBase.h"
#include "Attacks.h"

#ifndef ATTACKPATTERN_VERTICLEGAP_H
#define ATTACKPATTERN_VERTICLEGAP_H

class AttackPattern_VerticleGap : public AttackPatternBase
{
public:
	explicit AttackPattern_VerticleGap(int width, int height, Matrix &screen_matrix, PlayerDefinition &player);
	virtual ~AttackPattern_VerticleGap() {}

	// Setters
	void OnBeginAttack();
	void refreshScreen();
	void createAttack(int gap_position_x, int position_y);
protected:
	// Setters
	virtual void setAttackParameters() {}

	int create_attack_delay_, gap_width_, screen_duration_, attacks_created_, move_delay_, start_time_end_warning_, warning_length_;
};

class VerticleGap_VerySlow : public AttackPattern_VerticleGap
{
public:
	using AttackPattern_VerticleGap::AttackPattern_VerticleGap;

private:
	void setAttackParameters()
	{
		warning_length_ = 3000;
		create_attack_delay_ = 20;
		gap_width_ = 2;
		screen_duration_ = 20000;
		move_delay_ = 300;
	}
};

class VerticleGap_Slow : public AttackPattern_VerticleGap
{
public:
	using AttackPattern_VerticleGap::AttackPattern_VerticleGap;

private:
	void setAttackParameters()
	{
		warning_length_ = 3000;
		create_attack_delay_ = 20;
		gap_width_ = 4;
		screen_duration_ = 20000;
		move_delay_ = 80;
	}
};

class VerticleGap_Wavy : public AttackPattern_VerticleGap
{
public:
	using AttackPattern_VerticleGap::AttackPattern_VerticleGap;

private:
	void setAttackParameters()
	{
		warning_length_ = 3000;
		create_attack_delay_ = 50;
		gap_width_ = 8;
		screen_duration_ = 5000;
		move_delay_ = 8;
	}
};

class VerticleGap_VeryFast : public AttackPattern_VerticleGap
{
public:
	using AttackPattern_VerticleGap::AttackPattern_VerticleGap;

private:
	void setAttackParameters()
	{
		warning_length_ = 3000;
		create_attack_delay_ = 1;
		gap_width_ = 8;
		screen_duration_ = 5000;
		move_delay_ = 8;
	}
};

#endif // !ATTACKPATTERN_VERTICLEGAP_H
