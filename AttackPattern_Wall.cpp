#include "AttackPattern_Wall.h"

AttackPattern_Wall::AttackPattern_Wall(int width, int height, Matrix &screen_matrix, PlayerDefinition &player, int number_of_attacks, int gap_width, int speed)
	: AttackPatternBase(width, height, screen_matrix, player, number_of_attacks), gap_width_{ gap_width }, speed_{ speed }
{
}

// Calls once when the entire attack starts
void AttackPattern_Wall::OnBeginAttack()
{
	createAttack( 0, width_, generateRandomNumber(0, height_ - 1));
	start_time_new_attack_ = GetTickCount64();
	has_completed_initialization_ = true;
}

// Refreshes screen to show player/enemy positions
void AttackPattern_Wall::refreshScreen()
{
	if (created_attacks_ == attacks_to_create_ && attacks_list_.size() == 0)
		has_completed_all_attacks_ = true;
	else
	{
		double current_time_new_attack_ = GetTickCount64() - start_time_new_attack_;
		if (current_time_new_attack_ >= 1750 && created_attacks_ < attacks_to_create_) // Create new Attacks
		{
			createAttack( 0, width_, generateRandomNumber(0, height_ - 1));
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
void AttackPattern_Wall::createAttack(int min_position_x, int max_position_x, int gap_height)
{
	Attack_Wall *attack;
	attack = new Attack_Wall(width_, height_, player_position_, attack_matrix_, element_is_occupied_, min_position_x, max_position_x, gap_height, gap_width_, speed_);
	attacks_list_.push_back(attack);
	created_attacks_++;
}