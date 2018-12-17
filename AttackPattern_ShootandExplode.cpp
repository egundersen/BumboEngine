#include "AttackPattern_ShootAtPlayer.h"
#include "AttackPattern_ShootandExplode.h"
#include "AttackPattern_Explode.h"
#include "MatrixBase.h"
#include "Attacks.h"
#include "Image.h"
#include <algorithm>
#include <Windows.h>
AttackPattern_ShootandExplode::AttackPattern_ShootandExplode(int width, int height, Matrix& screen_matrix, int & player_health, int number_of_attacks)
	: AttackPatternBase(width, height, screen_matrix, player_health, number_of_attacks)
{
	attacks_to_create_ = number_of_attacks * 2;
}

// Calls once when the entire attack starts
void AttackPattern_ShootandExplode::OnBeginAttack()
{
	setAttackParameters();
	createAttack2(rand() % 2, 0, width_, 60, player_position_.y, 1);
	createAttack1(generateRandomNumber(attack_diameter_ / 2, width_ - attack_diameter_ / 2), generateRandomNumber(attack_diameter_ / 2, height_ - attack_diameter_ / 2));
	start_time_new_attack_ = GetTickCount64();
	has_completed_initialization_ = true;
}

// Refreshes screen to show player/enemy positions
void AttackPattern_ShootandExplode::refreshScreen()
{
	if (created_attacks_ == attacks_to_create_ && attacks_list_.size() == 0)
		has_completed_all_attacks_ = true;
	else
	{
		double current_time_new_attack_ = GetTickCount64() - start_time_new_attack_;
		if (current_time_new_attack_ >= 500 && created_attacks_ < attacks_to_create_) // Create new Attacks
		{
			createAttack2(rand() % 2, 0, width_, 60, player_position_.y, 1);
			createAttack1(generateRandomNumber(attack_diameter_ / 2, width_ - attack_diameter_ / 2), generateRandomNumber(attack_diameter_ / 2, height_ - attack_diameter_ / 2));
			start_time_new_attack_ = GetTickCount64();
		}

		attacksCheckCollision();
		moveAttack();

		evaluatePlayerInput();
		refreshPlayerLocation();
		displayScreen();
	}
}

// Add attack to list of attacks
void AttackPattern_ShootandExplode::createAttack2(int reverse_direction, int min_position_x, int max_position_x, int trail_length, int height_y, int speed)
{
	Attack_HorizontalLine *attack;
	if (reverse_direction == 1)
		attack = new HorizontalLine_Left(width_, height_, player_position_, matrix_, element_is_occupied_, min_position_x, max_position_x, trail_length, height_y, speed);
	else
		attack = new HorizontalLine_Right(width_, height_, player_position_, matrix_, element_is_occupied_, min_position_x, max_position_x, trail_length, height_y, speed);

	attacks_list_.push_back(attack);
	created_attacks_++;
}
void AttackPattern_ShootandExplode::createAttack1(int center_position_x, int center_position_y)
{
	Attack_Explode *attack;
	attack = new Attack_Explode(width_, height_, player_position_, matrix_, element_is_occupied_, center_position_x, center_position_y, attack_diameter_, delay_till_explode_, duration_of_explosion_);

	attacks_list_.push_back(attack);
	created_attacks_++;
}
