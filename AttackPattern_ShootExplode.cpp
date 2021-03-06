#include "AttackPattern_ShootExplode.h"

AttackPattern_ShootExplode::AttackPattern_ShootExplode(int width, int height, Matrix& screen_matrix, PlayerDefinition &player, int number_of_attacks)
	: AttackPatternBase(width, height, screen_matrix, player, number_of_attacks)
{
	attacks_to_create_ = number_of_attacks * 2;
}

// Calls once when the entire attack starts
void AttackPattern_ShootExplode::OnBeginAttack()
{
	setAttackParameters();
	created_attacks_++;
	createAttack1(generateRandomNumber(attack_diameter_ / 2, width_ - attack_diameter_ / 2), generateRandomNumber(attack_diameter_ / 2, height_ - attack_diameter_ / 2));
	start_time_new_attack_ = GetTickCount64();
	has_completed_initialization_ = true;
}

// Refreshes screen to show player/enemy positions
void AttackPattern_ShootExplode::refreshScreen()
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
void AttackPattern_ShootExplode::createAttack2(int reverse_direction, int min_position_x, int max_position_x, int trail_length, int height_y, int speed)
{
	Attack_HorizontalLineArrow *attack;
	if (reverse_direction == 1)
		attack = new HorizontalLineArrow_Left(width_, height_, player_position_, attack_matrix_, element_is_occupied_, min_position_x, max_position_x, trail_length, height_y, speed);
	else
		attack = new HorizontalLineArrow_Right(width_, height_, player_position_, attack_matrix_, element_is_occupied_, min_position_x, max_position_x, trail_length, height_y, speed);

	attacks_list_.push_back(attack);
	created_attacks_++;
}
void AttackPattern_ShootExplode::createAttack1(int center_position_x, int center_position_y)
{
	Attack_Explode *attack;
	attack = new Attack_Explode(width_, height_, player_position_, attack_matrix_, element_is_occupied_, center_position_x, center_position_y, attack_diameter_, delay_till_explode_, duration_of_explosion_);

	attacks_list_.push_back(attack);
	created_attacks_++;
}
