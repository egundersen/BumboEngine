#include "AttackPattern_Snake.h"

AttackPattern_Snake::AttackPattern_Snake(int width, int height, Matrix &screen_matrix, PlayerDefinition &player, int number_of_attacks, int duration_of_attack, int snake_speed)
	: AttackPatternBase(width, height, screen_matrix, player, number_of_attacks), duration_of_attack_{ duration_of_attack }, snake_speed_{ snake_speed }
{
}

// Calls once when the entire attack starts
void AttackPattern_Snake::OnBeginAttack()
{
	createAttack(0, generateRandomNumber(0, height_ - 1), duration_of_attack_, 50);
	start_time_new_attack_ = GetTickCount64();
	has_completed_initialization_ = true;
}

// Refreshes screen to show player/enemy positions
void AttackPattern_Snake::refreshScreen()
{
	if (created_attacks_ == attacks_to_create_ && attacks_list_.size() == 0)
		has_completed_all_attacks_ = true;
	else
	{
		double current_time_new_attack_ = GetTickCount64() - start_time_new_attack_;
		if (current_time_new_attack_ >= 4000 && created_attacks_ < attacks_to_create_) // Create new Attacks
		{
			createAttack(0, generateRandomNumber(0, height_ - 1), duration_of_attack_, 50);
			start_time_new_attack_ = GetTickCount64();
		}

		attacksCheckCollision();
		checkBorderCollision();
		double current_time_move_attack_ = GetTickCount64() - start_time_move_attack_;
		if (current_time_move_attack_ >= snake_speed_)
		{
			moveAttack();
			start_time_move_attack_ = GetTickCount64();
		}

		evaluatePlayerInput();
		refreshPlayerLocation();
		displayScreen();
	}
}

// Add attack to list of attacks
void AttackPattern_Snake::createAttack(int head_position_x, int head_position_y, int duration_of_attack, int speed)
{
	Attack_Snake *attack;
	attack = new Attack_Snake(width_, height_, player_position_, attack_matrix_, element_is_occupied_, head_position_x, head_position_y, duration_of_attack, speed);

	attacks_list_.push_back(attack);
	created_attacks_++;
}
