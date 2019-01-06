#include "AttackPattern_Explode.h"
#include "MatrixBase.h"
#include "Attacks.h"
#include "Image.h"
#include <windows.h>
#include <algorithm>

AttackPattern_Explode::AttackPattern_Explode(int width, int height, Matrix &screen_matrix, PlayerDefinition &player, int number_of_attacks)
	: AttackPatternBase(width, height, screen_matrix, player, number_of_attacks), create_attack_delay_{ 50 }, attack_diameter_{ 4 }, delay_till_explode_{ 1500 }, duration_of_explosion_{ 1000 }
{
}

// Calls once when the entire attack starts
void AttackPattern_Explode::OnBeginAttack()
{
	setAttackParameters();
	createBorder();
	createAttack(generateRandomNumber(attack_diameter_ / 2, width_ - attack_diameter_ / 2), generateRandomNumber(attack_diameter_ / 2, height_ - attack_diameter_ / 2));
	start_time_new_attack_ = GetTickCount64();
	has_completed_initialization_ = true;
}

// Refreshes screen to show player/enemy positions
void AttackPattern_Explode::refreshScreen()
{
	if (created_attacks_ == attacks_to_create_ && attacks_list_.size() == 0)
		has_completed_all_attacks_ = true;
	else
	{
		double current_time_new_attack_ = GetTickCount64() - start_time_new_attack_;
		if (current_time_new_attack_ >= create_attack_delay_ && created_attacks_ < attacks_to_create_) // Create new Attacks
		{
			createAttack(generateRandomNumber(attack_diameter_ / 2, width_ - attack_diameter_ / 2), generateRandomNumber(attack_diameter_ / 2, height_ - attack_diameter_ / 2));
			start_time_new_attack_ = GetTickCount64();
		}

		attacksCheckCollision();
		checkBorderCollision();
		moveAttack();

		evaluatePlayerInput();
		refreshPlayerLocation();
		displayScreen();
	}
}

// Add attack to list of attacks
void AttackPattern_Explode::createAttack(int center_position_x, int center_position_y)
{
	Attack_Explode *attack;
	attack = new Attack_Explode(width_, height_, player_position_, attack_matrix_, element_is_occupied_, center_position_x, center_position_y, attack_diameter_, delay_till_explode_, duration_of_explosion_);

	attacks_list_.push_back(attack);
	created_attacks_++;
}
