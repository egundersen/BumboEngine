#include "AttackPattern_HailStorm.h"

HailStorm::HailStorm(int width, int height, Matrix & screen_matrix, PlayerDefinition & player, int number_of_attacks, char direction, int slip_modifier, char slip_direction)
	: AttackPatternBase(width, height, screen_matrix, player, number_of_attacks), direction_{ direction }, slip_direction_{ slip_direction }, slip_modifier_{ slip_modifier }
{
	generateRandomSequence(attack_starting_positions_, 0, height_ - 1);
	max_starting_position_ = direction_ == 'u' || direction_ == 'd' ? width_ : height_;
}

void HailStorm::OnBeginAttack()
{
	createAttack(rand() % 2, generateRandomNumber(0, max_starting_position_), 1);
	start_time_new_attack_ = GetTickCount64();
	has_completed_initialization_ = true;
}

void HailStorm::refreshScreen()
{
	if (created_attacks_ == attacks_to_create_ && attacks_list_.size() == 0)
		has_completed_all_attacks_ = true;
	else
	{
		double current_time_new_attack_ = GetTickCount64() - start_time_new_attack_;
		if (current_time_new_attack_ >= 40 && created_attacks_ < attacks_to_create_) // Create new Attacks
		{
			createAttack(rand() % 2, generateRandomNumber(0, max_starting_position_), 1);
			start_time_new_attack_ = GetTickCount64();
		}

		attacksCheckCollision();
		moveAttack();

		evaluatePlayerInput();
		refreshPlayerLocation();
		displayScreen();
	}
}

void HailStorm::createAttack(int reverse_direction, int position_2D_, int speed)
{
	Attack_Dot *attack = new Attack_Dot(width_, height_, player_position_, attack_matrix_, element_is_occupied_, position_2D_, speed, direction_, slip_modifier_, slip_direction_);
	attacks_list_.push_back(attack);
	created_attacks_++;
}
